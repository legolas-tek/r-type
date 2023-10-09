/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network sync system
*/

#include "NetworkSyncSystem.hpp"

net::system::NetworkServerSync::NetworkServerSync(Registry &registry, int port)
    : _registry(registry), _nmu(net::server_netmanager, "0.0.0.0", port)
{
}

net::system::NetworkServerSync::~NetworkServerSync()
{
}

void net::system::NetworkServerSync::processReceivedPacket(std::pair<net::Buffer, net::manager::Udp::Client> const &packet)
{
    int offset = 0;

    for (auto it = packet.first.begin() + 9; it != packet.first.end();) {
        uint32_t entity_nbr = 0; /// Variable declared to store temporaly the entity number

        std::memcpy(&entity_nbr, &(*it), sizeof(entity_nbr));
        Entity entity(entity_nbr); /// Build an entity object from the entity number
        offset += sizeof(entity_nbr); /// Update the offset by the size of the entity number readed

        uint8_t component_id = 0; ///Variable declared to store the component id

        std::memcpy(&component_id, &*(it + offset), sizeof(component_id));
        offset += sizeof(component_id); /// Same, update the offsetbby the size of the component id readed

        bool updateType = 0;

        memcpy(&updateType, &*(it + offset), sizeof(updateType));
        offset += sizeof(updateType); /// Update for the  update type

        if (updateType)
            offset += _registry.apply_data(entity, component_id, &*(it + offset)); // apply the data update on the concerned entity if there's an update
        else
            _registry.erase_component(entity, component_id); /// else, erase the concerned component

        it += offset; /// Don't forget to update the offset ;)
    }
}

void net::system::NetworkServerSync::processAckPacket(std::pair<net::Buffer, net::manager::Udp::Client> const &packet)
{
    uint32_t tick_number = 0;

    std::memcpy(&tick_number, &*(packet.first.begin() + 1), sizeof(tick_number));

    auto snapshot_it = std::find_if(_snapshots.begin(), _snapshots.end(),
        [&](SnapshotHistory &i) {
            return i.snapshot.tick == tick_number;
    });

    auto &others = _nmu.getOthers();
    auto other_it = std::find_if(others.begin(), others.end(),
        [&] (net::manager::Udp::Client &i) {
            return i.getEndpoint() == packet.second.getEndpoint();
    });
    std::size_t index = other_it - others.begin();

    snapshot_it->ack_users.push_back(index);
}

void net::system::NetworkServerSync::operator()()
{
    auto _received_packets = _nmu.receive();

    if (not _received_packets.empty()) {
        for (auto &packet: _received_packets) { /// Loop threw all the received packets
            if (*packet.first.begin() == std::byte(0x01)) // If case identifier = 0x01 then it's a state update
                this->processReceivedPacket(packet);
            if (*packet.first.begin() == std::byte(0x02)) // If case identifier = 0x02 then it's an ack packet
                this->processAckPacket(packet);
        }
    }
}
