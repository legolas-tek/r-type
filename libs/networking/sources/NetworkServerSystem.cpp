/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network server system
*/

#include "NetworkServerSystem.hpp"

net::system::NetworkServer::NetworkServer(
    engine::Registry &registry, int port,
    std::vector<net::lobby::RemoteClient> const &lobby
)
    : Sync(net::server_netmanager, registry, "0.0.0.0", port, lobby)
{
}

net::system::NetworkServer::~NetworkServer() = default;

bool net::system::NetworkServer::canUpdate(
    [[maybe_unused]] manager::Client const &client,
    [[maybe_unused]] engine::Entity entity,
    [[maybe_unused]] uint8_t component_id,
    [[maybe_unused]] engine::Deserializer deser
)
{
    return false;
}
