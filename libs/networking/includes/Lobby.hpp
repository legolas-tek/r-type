/*
** EPITECH PROJECT, 2023
** RType Networking
** File description:
** Lobby
*/

#ifndef RTYPE_NETWORKING_LOBBY_HPP
#define RTYPE_NETWORKING_LOBBY_HPP

#include "LobbyServer.hpp"
#include <random>

namespace net::lobby {

class Lobby;

/**
 * @brief The lobby remote client, which represents a connection to an online
 * lobby client
 *
 * This class contains functions to interact with the remote lobby client, over
 * a tcp connection. This is a System, but it is designed to work as a subsystem
 * of the Lobby system.
 *
 * It is an implementation of LobbyRemoteClient, which works in the standard
 * way.
 */
class RemoteClient : public LobbyRemoteClient {
public:
    /**
     * @brief Construct a new Lobby Remote Client object
     *
     * @param network The network connection to use
     */
    RemoteClient(manager::TcpConnection &&network, Lobby &parent);

public:
    /**
     * @brief The exception thrown when the game should start
     *
     * This exception is thrown when the game should start, and is caught by
     * the main, which then starts the real game.
     */
    class StartGameException : public std::exception {
    public:
        char const *what() const noexcept override;
    };

private:
    /// Called when the client sends a join request
    void onJoinRequest(std::string &&playerName) override;
    /// Called when the client sends a start request
    void onStartRequest() override;

private:
    /// The name of the player
    std::string _playerName;
    size_t _playerNumber;
    size_t _playerHash;
    /// The parent lobby server
    Lobby &_parent;
};

/**
 * @brief The lobby server, which uses a tcp server to accept new connections
 *
 * This class implements a Lobby in the standard way, according to the
 * documented lobby protocol
 */
class Lobby : public LobbyServer<RemoteClient> {
public:
    /**
     * @brief Construct a new Lobby Server object
     *
     * @param port The port to listen on
     */
    Lobby(std::size_t port, std::size_t maxPlayers);

    void emplaceClient(manager::TcpConnection &&connection) override;

    friend class RemoteClient;

private:
    /// The vector of players that have joined the lobby
    std::vector<RemoteClient *> _players;
    /// The maximum number of players that can join the lobby
    std::size_t _maxPlayers;
    /// The random device used to generate player hashes
    std::random_device _random;
    /// The distribution used to generate player hashes
    std::uniform_int_distribution<size_t> _dist;
};
}

#endif /* !RTYPE_NETWORKING_LOBBY_HPP */
