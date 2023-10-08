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

void net::system::NetworkServerSync::operator()()
{
    auto _received_packets = _nmu.receive();
    std::size_t offset = 0;

    if (not _received_packets.empty()) {
        for (auto &packet: _received_packets) { /// Loop threw all the received packets
            for (auto it = packet.first.begin() + 9; it != packet.first.end();) {
                uint32_t entity_nbr = 0; /// Variable declared to store temporaly the entity number

                std::memcpy(&entity_nbr, &(*it), 4);
                Entity entity(entity_nbr); /// Build an entity object from the entity number
                offset += 4; /// Update the offset by the size of the entity number readed

                uint8_t component_id = 0; ///Variable declared to store the component id

                std::memcpy(&component_id, &*(it + offset), 1);
                offset += 1; /// Same, update the offsetbby the size of the component id readed

                bool updateType = 0;

                memcpy(&updateType, &*(it + offset), 1);
                offset += 1; /// Update for the  update type

                if (updateType)
                    offset += _registry.apply_data(entity, component_id, &*(it + offset)); // apply the data update on the concerned entity if there's an update
                else
                    _registry.erase_component(entity, component_id); /// else, erase the concerned component

                it += offset; /// Don't forget to update the offset ;)
            }
        }
    }

}
