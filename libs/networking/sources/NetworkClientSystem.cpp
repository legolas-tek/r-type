/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network client system
*/

#include "NetworkClientSystem.hpp"

net::system::NetworkClient::NetworkClient(
    engine::Registry &registry, std::string const &addr, int port,
    size_t playerNumber, size_t playerHash
)
    : Sync(
        net::client_netmanager, registry, addr, port, playerNumber, playerHash
    )
{
}

net::system::NetworkClient::~NetworkClient() = default;

bool net::system::NetworkClient::canSend(
    engine::Entity entity, uint8_t component_id
)
{
    return true;
}
