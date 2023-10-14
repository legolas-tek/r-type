/*
** EPITECH PROJECT, 2023
** RType Networking
** File description:
** Lobby protocol
*/

#ifndef RTYPE_NETWORKING_LOBBY_CLIENT_HPP
#define RTYPE_NETWORKING_LOBBY_CLIENT_HPP

#include "ISystem.hpp"

#include <cstdint>
#include <memory>
#include <string>

namespace net {

namespace manager {
class Tcp;
}

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
    std::unique_ptr<net::manager::Tcp> _network;
};
}

#endif /* !RTYPE_NETWORKING_LOBBY_CLIENT_HPP */
