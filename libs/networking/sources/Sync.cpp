/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network Sync abstract class
*/

#include "Serialization/Deserializer.hpp"
#include "Serialization/Serializer.hpp"
#include "Snapshot.hpp"
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
    [[maybe_unused]] engine::Entity entity,
    [[maybe_unused]] uint8_t component_id,
    [[maybe_unused]] engine::Deserializer deser
)
{
    return true;
}

void net::Sync::sendAckPacket(
    uint32_t tickNumber, net::manager::Client const &client
)
{
    engine::Serializer serializer;

    serializer.serializeTrivial(std::byte(0x02));
    serializer.serializeTrivial(tickNumber);
    _nmu->send(serializer.finalize(), client);

#ifdef DEBUG_NETWORK
    std::cout << "SyncSystem: sent ack packet for tick " << tickNumber
              << std::endl;
#endif
}

void net::Sync::processUpdatePacket(
    engine::Deserializer &deserializer, net::manager::Client const &client
)
{
    uint32_t tickNumber;
    deserializer.deserializeTrivial(tickNumber);

    deserializer.skip(sizeof(uint32_t)); // skip the previous tick number

    while (not deserializer.isFinished()) {
        uint32_t entity_nbr = 0;
        deserializer.deserializeTrivial(entity_nbr);

        if (entity_nbr >= 500)
            // invalid entity number
            return;

        engine::Entity entity(entity_nbr);

        uint8_t component_id = 0;
        deserializer.deserializeTrivial(component_id);

        bool updateType = 0;
        deserializer.deserializeTrivial(updateType);

        if (not canUpdate(entity, component_id, deserializer)) {
            // update disallowed, use the trash entity
            entity = engine::Entity(0);
        }

        if (updateType) {
            // apply the update
            _registry.apply_data(entity, component_id, deserializer);
        }

        if (not updateType or entity == 0) {
            // erase the component, or the trash entity
            _registry.erase_component(entity, component_id);
        }
    }

#ifdef DEBUG_NETWORK
    std::cout << "SyncSystem: received " << deserializer.getOffset()
              << " byte update packet for tick " << tickNumber << std::endl;
#endif

    sendAckPacket(tickNumber, client);
}

void net::Sync::processAckPacket(
    engine::Deserializer &deserializer, net::manager::Client const &client
)
{
    uint32_t tick_number = 0;
    deserializer.deserializeTrivial(tick_number);

#ifdef DEBUG_NETWORK
    std::cout << "SyncSystem: received ack of tick " << tick_number
              << std::endl;
#endif

    auto snapshot_it = std::find_if(
        _snapshots.begin(), _snapshots.end(),
        [&](SnapshotHistory &i) { return i.snapshot.tick == tick_number; }
    );

    if (snapshot_it == _snapshots.end())
        return;

    auto &others = _nmu->getOthers();
    auto other_it = std::find_if(
        others.begin(), others.end(),
        [&](net::manager::Client &i) {
            return i.getEndpoint() == client.getEndpoint();
        }
    );
    std::size_t index = other_it - others.begin();

    // mark the snapshot as acked by the client number by its index
    snapshot_it->ack_mask |= (1 << index);
}

net::Snapshot &net::Sync::find_last_ack(std::size_t client_index)
{
    for (int i = 0; i != net::NET_SNAPSHOT_NBR; ++i) {
        unsigned int index = (_rd_index - i) % net::NET_SNAPSHOT_NBR;

        auto &snapshot = _snapshots[index];

        if (snapshot.snapshot.wasAck) {
            // use the dummy snapshot, which is always acked
            return snapshot.snapshot;
        }

        if (snapshot.ack_mask & (1 << client_index)) {
            // the snapshot was acked by the client
            return snapshot.snapshot;
        }
    }

    return _dummy;
}

static std::vector<std::byte> constructUpdatePacket(
    net::Snapshot const &previous, net::Snapshot const &current
)
{
    engine::Serializer serializer;

    serializer.serializeTrivial(std::byte(0x01));
    serializer.serializeTrivial(std::uint32_t(current.tick));
    serializer.serializeTrivial(std::uint32_t(previous.tick));

    size_t size = serializer.getSize();
    net::diffSnapshots(serializer, previous, current);
    if (serializer.getSize() == size) {
        return {}; // no update
    }
    return serializer.finalize();
}

void net::Sync::updateSnapshotHistory(net::Snapshot &&current)
{
    SnapshotHistory &snap = _snapshots[_rd_index % NET_SNAPSHOT_NBR];

    snap.snapshot = std::move(current);
    snap.ack_mask = 0;
    _rd_index = (_rd_index + 1) % NET_SNAPSHOT_NBR;
}

void net::Sync::operator()()
{
    auto _received_packets = _nmu->receive();

    for (auto &[buffer, client] : _received_packets) {
        engine::Deserializer deserializer(buffer);
        std::uint8_t packet_id = 0;
        deserializer.deserializeTrivial(packet_id);
        switch (packet_id) {
        case 0x01:
            processUpdatePacket(deserializer, client);
            break;
        case 0x02:
            processAckPacket(deserializer, client);
            break;
        }
    }

    auto &clients = _nmu->getOthers();

    for (auto it = clients.begin(); it != clients.end(); it++) {
        Snapshot &previous = find_last_ack(it - clients.begin());
        Snapshot current(_registry.getTick(), _registry);

        auto packet = constructUpdatePacket(previous, current);

        if (packet.empty())
            continue;
        updateSnapshotHistory(std::move(current));

#ifdef DEBUG_NETWORK
        std::cout << "SyncSystem: sent " << packet.size()
                  << " byte update packet for tick " << _registry.getTick()
                  << std::endl;
#endif
        _nmu->send(packet, *it);
    }
}
