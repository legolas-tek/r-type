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
