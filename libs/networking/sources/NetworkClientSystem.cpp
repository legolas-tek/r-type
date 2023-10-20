/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network client system
*/

#include "NetworkClientSystem.hpp"

net::system::NetworkClient::NetworkClient(
    engine::Registry &registry, int port, size_t playerNumber, size_t playerHash
)
    : Sync(net::client_netmanager, registry, port, playerNumber, playerHash)
{
}

net::system::NetworkClient::~NetworkClient()
{
}
