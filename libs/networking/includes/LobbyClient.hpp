/*
** EPITECH PROJECT, 2023
** RType Networking
** File description:
** Lobby protocol
*/

#ifndef RTYPE_NETWORKING_LOBBY_CLIENT_HPP
#define RTYPE_NETWORKING_LOBBY_CLIENT_HPP

#include "ISystem.hpp"
#include "TcpConnection.hpp"

#include <cstdint>
#include <memory>
#include <string>

namespace net {

namespace manager {
class Tcp;
}

/**
 * @brief The lobby client, which connects to an online lobby server
 *
 * This class contains functions to interact with the lobby server, over a tcp
 * connection. This is a System, so it must be added to a Registry.
 */
class LobbyClient : public ISystem {
public:
    /// Create a new Client, connecting to the server at the given address
    LobbyClient(std::string const &addr, std::size_t port);

    /// Send a Join Request with the given player name
    void sendJoinRequest(std::string const &playerName);
    /// Send a Start Request
    void sendStartRequest();

    /// Checks for incoming messages from the server, and handles them
    void operator()() override;

private:
    /// Parses an incoming packet
    void parsePacket();

private:
    /// Called when the server sends a "Join Success" packet
    virtual void
    onJoinSuccess(std::uint8_t playerNumber, std::uint64_t playerHash)
        = 0;

    /// Called when the server sends a "New Player" packet
    virtual void
    onNewPlayer(std::uint8_t playerNumber, std::string &&playerName)
        = 0;

    /// Called when the server sends a "Game Start" packet
    virtual void onGameStart() = 0;

    /// Called when the server sends an error packet
    virtual void onError(std::string &&errorMessage) = 0;

private:
    /// The underlying tcp connection
    net::manager::TcpConnection _network;
};
}

#endif /* !RTYPE_NETWORKING_LOBBY_CLIENT_HPP */
