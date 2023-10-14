/*
** EPITECH PROJECT, 2023
** RType Networking
** File description:
** Lobby protocol
*/

#ifndef RTYPE_NETWORKING_LOBBYPROTOCOL_HPP
#define RTYPE_NETWORKING_LOBBYPROTOCOL_HPP

#include "ISystem.hpp"
#include "TcpNetManager.hpp"
#include <cstdint>

namespace net {

class LobbyClient : public ISystem {
public:
    LobbyClient(std::string addr, std::size_t port);

    void sendJoinRequest(std::string const &playerName);
    void sendStartRequest();

    void operator()() override;

private:
    void parsePacket();

private:
    virtual void
    onJoinSuccess(std::uint8_t playerNumber, std::uint64_t playerHash)
        = 0;

    virtual void
    onNewPlayer(std::uint8_t playerNumber, std::string &&playerName)
        = 0;

    virtual void onGameStart() = 0;

    virtual void onError(std::string &&errorMessage) = 0;

private:
    net::manager::Tcp _network;
};
}

#endif /* !RTYPE_NETWORKING_LOBBYPROTOCOL_HPP */
