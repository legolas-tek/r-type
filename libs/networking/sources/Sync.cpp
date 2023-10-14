/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network Sync abstract class
*/

#include "UdpNetManager.hpp"

#include "Sync.hpp"

net::Sync::Sync(net::ClientNetManager, engine::Registry &registry, int port)
    : _registry(registry)
    , _nmu(std::make_unique<net::manager::Udp>(
          net::client_netmanager, "127.0.0.1", port
      ))
    , _rd_index(0)
{
}

net::Sync::Sync(net::ServerNetManager, engine::Registry &registry, int port)
    : _registry(registry)
    , _nmu(std::make_unique<net::manager::Udp>(
          net::server_netmanager, "0.0.0.0", port
      ))
    , _rd_index(0)
{
}

net::Sync::~Sync()
{
}

bool net::Sync::canUpdate(
    engine::Entity entity, uint8_t component_id, std::byte const *buffer
)
{
    return true;
}

void net::Sync::sendAckPacket(
    uint32_t tickNumber, net::manager::Client const &client
)
{
    std::vector<std::byte> response(
        sizeof(std::byte) + sizeof(uint32_t), std::byte(0x02)
    );

#ifdef DEBUG_NETWORK
    std::cout << "SyncSystem: sent ack packet for tick " << tickNumber
              << std::endl;
#endif

    response.at(0) = std::byte(0x02);
    std::memcpy(&*(response.begin() + 1), &tickNumber, sizeof(uint32_t));
    _nmu->send(response, client);
}

void net::Sync::processUpdatePacket(
    std::pair<net::Buffer, net::manager::Client> const &packet
)
{

    for (auto it = packet.first.begin() + 9; it != packet.first.end();) {
        uint32_t entity_nbr = 0; /// Variable declared to store temporarily the entity number

        std::memcpy(&entity_nbr, &(*it), sizeof(entity_nbr));
        if (entity_nbr >= 500) /// If the entity number isn't valid don;t
                               /// process the packet
            return;

        engine::Entity entity(entity_nbr); /// Build an entity object from the entity number
        it += sizeof(entity_nbr); /// Update the offset by the size of the entity number readed

        uint8_t component_id = 0; ///Variable declared to store the component id

        std::memcpy(&component_id, &*(it), sizeof(component_id));
        it += sizeof(component_id); /// Same, update the offsetbby the size of the component id readed

        bool updateType = 0;

        memcpy(&updateType, &*(it), sizeof(updateType));
        it += sizeof(updateType); /// Update for the  update type

        if (not canUpdate(
                entity, component_id, &*it
            )) /// If the server don't accept the update, don't update
            entity = engine::Entity(0);

        if (updateType)
            it += _registry.apply_data(entity, component_id, &*(it)); // apply the data update on the concerned entity if there's an update

        if (not updateType or entity == 0) /// else, erase the component
            _registry.erase_component(entity, component_id);
    }

    uint32_t tickNumber;

    std::memcpy(&tickNumber, &*(packet.first.begin() + 1), sizeof(tickNumber));

#ifdef DEBUG_NETWORK
    std::cout << "SyncSystem: received " << packet.first.size()
              << " byte update packet for tick " << tickNumber << std::endl;
#endif

    sendAckPacket(tickNumber, packet.second);
}

void net::Sync::processAckPacket(
    std::pair<net::Buffer, net::manager::Client> const &packet
)
{

    uint32_t tick_number = 0;

    std::memcpy(&tick_number, &*(packet.first.begin() + 1), sizeof(tick_number));

#ifdef DEBUG_NETWORK
    std::cout << "SyncSystem: received ack of tick " << tick_number
              << std::endl;
#endif

    auto snapshot_it = std::find_if(_snapshots.begin(), _snapshots.end(),
        [&](SnapshotHistory &i) {
            return i.snapshot.tick == tick_number;
    });

    if (snapshot_it == _snapshots.end())
        return;

    auto &others = _nmu->getOthers();
    auto other_it = std::find_if(
        others.begin(), others.end(),
        [&](net::manager::Client &i) {
            return i.getEndpoint() == packet.second.getEndpoint();
        }
    );
    std::size_t index = other_it - others.begin();

    if (std::find(snapshot_it->ack_users.begin(), snapshot_it->ack_users.end(), index) == snapshot_it->ack_users.end()) {
        snapshot_it->ack_users.push_back(index);
    }
}

net::Snapshot &net::Sync::find_last_ack(std::size_t client_index)
{
    for (int i = 0; i != net::NET_SNAPSHOT_NBR; ++i) {
        unsigned int index = (_rd_index - i) % net::NET_SNAPSHOT_NBR;

        auto &snapshot = _snapshots[index];

        if (std::find(
                snapshot.ack_users.begin(), snapshot.ack_users.end(),
                client_index
            )
            != snapshot.ack_users.end())
            return snapshot.snapshot;
    }

    return _dummy;
}

static std::vector<std::byte> constructUpdatePacket(
    uint32_t currentTick, uint32_t previousTick, std::vector<std::byte> diff
)
{
    std::vector<std::byte> result(sizeof(std::byte) + (sizeof(uint32_t) * 2), std::byte(0x00));
    auto it = result.begin();

    std::byte packetId{0x01};

    std::memcpy(&*it, &packetId, sizeof(std::byte));
    it++;

    std::memcpy(&*it, &currentTick, sizeof(uint32_t));
    it += sizeof(uint32_t);


    std::memcpy(&*it, &previousTick, sizeof(uint32_t));
    it += sizeof(uint32_t);

    result.insert(it, diff.begin(), diff.end());
    return result;
}

void net::Sync::updateSnapshotHistory(net::Snapshot &current)
{
    SnapshotHistory &snap = _snapshots[_rd_index % NET_SNAPSHOT_NBR];

    snap.used = 1;
    snap.snapshot = current;

    _rd_index = (_rd_index + 1) % NET_SNAPSHOT_NBR;
}

void net::Sync::operator()()
{
    auto _received_packets = _nmu->receive();

    if (not _received_packets.empty()) {
        for (auto &packet: _received_packets) { /// Loop threw all the received packets
            if (*packet.first.begin() == std::byte(0x01)) // In case identifier = 0x01 then it's a state update
                this->processUpdatePacket(packet);
            if (*packet.first.begin() == std::byte(0x02)) { // In case identifier = 0x02 then it's an ack packet
                this->processAckPacket(packet);
            }
        }
    }

    auto &clients = _nmu->getOthers();

    for (auto it = clients.begin(); it != clients.end(); it++) {
        Snapshot &previous = find_last_ack(it - clients.begin());
        Snapshot current(_registry.getTick(), _registry);

        std::vector<std::byte> diff = net::diffSnapshots(previous, current);

        if (not diff.empty()) {
            updateSnapshotHistory(current);
            auto packet = constructUpdatePacket(
                _registry.getTick(), _snapshots.at(_rd_index).snapshot.tick,
                diff
            );

#ifdef DEBUG_NETWORK
            std::cout << "SyncSystem: sent " << packet.size()
                      << " byte update packet for tick " << _registry.getTick()
                      << std::endl;
#endif
            _nmu->send(packet, *it);
        }
    }
}
