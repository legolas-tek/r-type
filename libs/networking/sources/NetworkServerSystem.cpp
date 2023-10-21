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

net::system::NetworkServer::~NetworkServer() = default;

bool net::system::NetworkServer::canUpdate(
    [[maybe_unused]] engine::Entity entity,
    [[maybe_unused]] uint8_t component_id,
    [[maybe_unused]] engine::Deserializer deser
)
{
    return false;
}
