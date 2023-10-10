/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network sync system
*/

#include "NetworkSyncSystem.hpp"

net::system::NetworkServerSync::NetworkServerSync(engine::Registry &registry, int port)
    : _registry(registry), _nmu(net::server_netmanager, "0.0.0.0", port), _snapshots(32, SnapshotHistory()), _rd_index(0)
{
}

net::system::NetworkServerSync::~NetworkServerSync()
{
}

void net::system::NetworkServerSync::processReceivedPacket(std::pair<net::Buffer, net::manager::Udp::Client> const &packet)
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

void net::system::NetworkServerSync::processAckPacket(std::pair<net::Buffer, net::manager::Udp::Client> const &packet)
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

std::vector<net::system::NetworkServerSync::SnapshotHistory>::iterator net::system::NetworkServerSync::find_last_ack(net::manager::Udp::Client const &client)
{
    auto result = _snapshots.begin() + _rd_index;

    if (result == _snapshots.begin() && _snapshots.back().used == 0)
        return _snapshots.end();

    if (result != _snapshots.begin()) {
        result = std::find_if(result, _snapshots.begin(),
            [] (SnapshotHistory &i) {
                return i.used == 1;
        });
    }

    if (result == _snapshots.begin()) {
        result = std::find_if(_snapshots.end(), _snapshots.begin() + _rd_index,
            [] (SnapshotHistory &i) {
                return i.used == 1;
        });
    }

    return result;
}

static std::vector<std::byte> constructUpdatePacket(std::size_t actualTick, std::size_t previousTick, std::vector<std::byte> diff)
{
    std::vector<std::byte> result(sizeof(std::byte) + (sizeof(uint32_t) * 2));

    result.at(0) = std::byte(0x01);
    std::memcpy(&result, &actualTick, sizeof(uint32_t));
    std::memcpy(&result, &previousTick, sizeof(uint32_t));
    result.insert(result.end(), diff.begin(), diff.end());

    return result;
}

void net::system::NetworkServerSync::updateSnapshotHistory(std::vector<std::byte> &componentData)
{

}

void net::system::NetworkServerSync::operator()()
{
    auto _received_packets = _nmu.receive();

    if (not _received_packets.empty()) {
        for (auto &packet: _received_packets) { /// Loop threw all the received packets
            if (*packet.first.begin() == std::byte(0x01)) // In case identifier = 0x01 then it's a state update
                this->processReceivedPacket(packet);
            if (*packet.first.begin() == std::byte(0x02)) // In case identifier = 0x02 then it's an ack packet
                this->processAckPacket(packet);
        }
    }

    auto &clients = _nmu.getOthers();

    for (auto &client: clients) {
        auto snapshot_it = find_last_ack(client);

        std::vector<std::byte> actualDiff = net::diffSnapshots(snapshot_it->snapshot, Snapshot(_registry.getTick(), _registry));

        if (not actualDiff.empty()) {
            updateSnapshotHistory(actualDiff);
            auto packet = constructUpdatePacket(_registry.getTick(), snapshot_it->snapshot.tick, actualDiff);
            _nmu.send(packet, client);
        }
    }
}
