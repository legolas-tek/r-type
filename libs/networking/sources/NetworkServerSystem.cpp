/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network server system
*/

#include "NetworkServerSystem.hpp"

net::system::NetworkServer::NetworkServer(engine::Registry &registry, int port)
    : Sync(net::server_netmanager, registry, port)
{
}

net::system::NetworkServer::~NetworkServer()
{
}

bool net::system::NetworkServer::canUpdate(
    engine::Entity entity, [[maybe_unused]] uint8_t component_id,
    [[maybe_unused]] std::byte const *buffer
)
{
    entity = engine::Entity(0);
    return true;
}
