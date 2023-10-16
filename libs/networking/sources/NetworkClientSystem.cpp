/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network client system
*/

#include "NetworkClientSystem.hpp"

net::system::NetworkClient::NetworkClient(engine::Registry &registry, int port)
    : Sync(net::client_netmanager, registry, port)
{
}

net::system::NetworkClient::~NetworkClient()
{
}


