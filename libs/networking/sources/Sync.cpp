/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network Sync abstract class
*/

#include "Sync.hpp"

net::Sync::Sync(net::ClientNetManager, engine::Registry &registry, int port)
    : _registry(registry), _nmu(net::client_netmanager, "0.0.0.0", port), _snapshots(32, SnapshotHistory()), _rd_index(0)
{
}

net::Sync::Sync(net::ServerNetManager, engine::Registry &registry, int port)
    : _registry(registry), _nmu(net::server_netmanager, "0.0.0.0", port), _snapshots(32, SnapshotHistory()), _rd_index(0)
{
}

net::Sync::~Sync()
{
}

bool net::Sync::canUpdate(engine::Entity &entity, uint8_t component_id, std::byte const *buffer)
{
    return true;
}

void net::Sync::processReceivedPacket(std::pair<net::Buffer, net::manager::Udp::Client> const &packet)
{
    for (auto it = packet.first.begin() + 9; it != packet.first.end();) {
        uint32_t entity_nbr = 0; /// Variable declared to store temporarily the entity number

        std::memcpy(&entity_nbr, &(*it), sizeof(entity_nbr));
        engine::Entity entity(entity_nbr); /// Build an entity object from the entity number
        it += sizeof(entity_nbr); /// Update the offset by the size of the entity number readed

        uint8_t component_id = 0; ///Variable declared to store the component id

        std::memcpy(&component_id, &*(it), sizeof(component_id));
        it += sizeof(component_id); /// Same, update the offsetbby the size of the component id readed

        bool updateType = 0;

        memcpy(&updateType, &*(it), sizeof(updateType));
        it += sizeof(updateType); /// Update for the  update type

        if (updateType)
            it += _registry.apply_data(entity, component_id, &*(it)); // apply the data update on the concerned entity if there's an update
        else
            _registry.erase_component(entity, component_id); /// else, erase the concerned component
    }

    std::vector<std::byte> response(1, std::byte(0x02));
    _nmu.send(response, packet.second);

}

void net::Sync::processAckPacket(std::pair<net::Buffer, net::manager::Udp::Client> const &packet)
{
    uint32_t tick_number = 0;

    std::memcpy(&tick_number, &*(packet.first.begin() + 1), sizeof(tick_number));

    auto snapshot_it = std::find_if(_snapshots.begin(), _snapshots.end(),
        [&](SnapshotHistory &i) {
            return i.snapshot.tick == tick_number;
    });

    if (snapshot_it == _snapshots.end())
        return;

    auto &others = _nmu.getOthers();
    auto other_it = std::find_if(others.begin(), others.end(),
        [&] (net::manager::Udp::Client &i) {
            return i.getEndpoint() == packet.second.getEndpoint();
    });
    std::size_t index = other_it - others.begin();

    if (std::find(snapshot_it->ack_users.begin(), snapshot_it->ack_users.end(), index) == snapshot_it->ack_users.end())
        snapshot_it->ack_users.push_back(index);
}

std::optional<std::vector<net::Sync::SnapshotHistory>::iterator> net::Sync::find_last_ack(std::size_t client_index)
{
    auto it = _snapshots.begin() + _rd_index;

    if (_rd_index == 0 && it->used == 0 && _snapshots.back().used == 0)
        return std::nullopt;

    if (it != _snapshots.begin()) {
        auto first = _snapshots.rbegin() + (_snapshots.size() - _rd_index);
        auto result = std::find_if(first, _snapshots.rend(),
            [&] (SnapshotHistory &i) {
                return i.used == 1 && (std::find(i.ack_users.begin(), i.ack_users.end(), client_index) != i.ack_users.end());
        });

        if (result != _snapshots.rend()) {
            return _snapshots.begin() + std::distance(result, _snapshots.rend()) - 1;
        }
    }

    auto last = _snapshots.rbegin() + (_snapshots.size() - _rd_index);
    auto result = std::find_if(_snapshots.rbegin(), last,
        [&] (SnapshotHistory &i) {
            return i.used == 1 && (std::find(i.ack_users.begin(), i.ack_users.end(), client_index) != i.ack_users.end());
    });

    if (result != last) {
        return _snapshots.begin() + std::distance(result, _snapshots.rend()) - 1;
    }

    return std::nullopt;
}

static std::vector<std::byte> constructUpdatePacket(std::size_t actualTick, std::size_t previousTick, std::vector<std::byte> diff)
{
    std::vector<std::byte> result(sizeof(std::byte) + (sizeof(uint32_t) * 2), std::byte(0x00));

    result.at(0) = std::byte(0x01);
    std::memcpy(&result, &actualTick, sizeof(uint32_t));
    std::memcpy(&result, &previousTick, sizeof(uint32_t));
    result.insert(result.end(), diff.begin(), diff.end());
    return result;
}

void net::Sync::updateSnapshotHistory(net::Snapshot &current)
{
    if (_rd_index + 1 > _snapshots.size()) {
        SnapshotHistory &snap = _snapshots.at(0);

        snap.used = 1;
        snap.snapshot = current;

        _rd_index = 0;
        return;
    }

    SnapshotHistory &snap = _snapshots.at(_rd_index + 1);

    snap.used = 1;
    snap.snapshot = current;

    _rd_index++;
}

void net::Sync::operator()()
{
    auto _received_packets = _nmu.receive();

    std::cout << "Helo" << std::endl;
    if (not _received_packets.empty()) {
        std::cout << "received" <<std::endl;
        for (auto &packet: _received_packets) { /// Loop threw all the received packets
            if (*packet.first.begin() == std::byte(0x01)) // In case identifier = 0x01 then it's a state update
                this->processReceivedPacket(packet);
            if (*packet.first.begin() == std::byte(0x02)) // In case identifier = 0x02 then it's an ack packet
                this->processAckPacket(packet);
        }
    }

    auto &clients = _nmu.getOthers();

    for (auto it = clients.begin(); it != clients.end(); it++) {
        std::cout << "A client" << std::endl;
        auto snapshot_it = find_last_ack(it - clients.begin());
        Snapshot current(_registry.getTick(), _registry);
        std::vector<std::byte> actualDiff;

        if (not snapshot_it) {
            std::cout << "whay" << std::endl;
            Snapshot dummy;
            actualDiff = net::diffSnapshots(dummy, current);
            std::cout << "oulala" << std::endl;
        } else
            actualDiff = net::diffSnapshots(snapshot_it.value()->snapshot, current);


        if (not actualDiff.empty()) {
            updateSnapshotHistory(current);
            auto packet = constructUpdatePacket(_registry.getTick(), _snapshots.at(_rd_index).snapshot.tick, actualDiff);
            std::cout << "whut" <<std::endl;
            _nmu.send(packet, *it);
        }
    }
}
