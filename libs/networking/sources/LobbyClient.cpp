/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** Lobby client
*/

#include "LobbyManager.hpp"
#include "TcpNetManager.hpp"

#include <algorithm>

net::LobbyClient::LobbyClient(std::string addr, std::size_t port)
    : _network(addr, port)
{
}

void net::LobbyClient::sendJoinRequest(std::string const &playerName)
{
    size_t playerNameSize = std::min(playerName.size(), 0xffUL);
    std::vector<std::byte> data(2 + playerNameSize, std::byte(0));

    data[0] = std::byte(0x01);
    data[1] = std::byte(playerNameSize);
    std::memcpy(&data[2], playerName.data(), playerNameSize);

    _network.write(data);
}

void net::LobbyClient::sendStartRequest()
{
    std::vector<std::byte> data(1, std::byte(0x08));

    _network.write(data);
}
