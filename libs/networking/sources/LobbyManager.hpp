/*
** EPITECH PROJECT, 2023
** RType Networking
** File description:
** Lobby protocol
*/

#ifndef RTYPE_NETWORKING_LOBBYPROTOCOL_HPP
#define RTYPE_NETWORKING_LOBBYPROTOCOL_HPP

#include "TcpNetManager.hpp"

namespace net {

class LobbyClient {
public:
    explicit LobbyClient(std::string addr, std::size_t port);

    void sendJoinRequest(std::string const &playerName);
    void sendStartRequest();

private:
    net::manager::Tcp _network;
};

}

#endif /* !RTYPE_NETWORKING_LOBBYPROTOCOL_HPP */
