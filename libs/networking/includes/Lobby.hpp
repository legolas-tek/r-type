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

    /// Get the player name
    [[nodiscard]] std::string const &getPlayerName() const;
    /// Get the player number
    [[nodiscard]] size_t getPlayerNumber() const;
    /// Get the player hash
    [[nodiscard]] size_t getPlayerHash() const;

private:
    /// Called when the client sends a join request
    void onJoinRequest(std::string &&playerName) override;
    /// Called when the client sends a spectate request
    void onSpectateRequest() override;
    /// Called when the client sends a start request
    void onStartRequest() override;

private:
    /// The name of the player
    std::string _playerName;
    /// The player number (1-maxPlayers), or 0 if not joined or spectator
    size_t _playerNumber = 0;
    /// The player hash, a random number used to identify the player uniquely,
    /// or 0 if not joined
    size_t _playerHash = 0;
    /// The parent lobby server
    Lobby &_parent;

    friend class Lobby;
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

    /// Get the current number of players in the lobby
    [[nodiscard]] std::size_t getCurrentPlayerCount() const;

    friend class RemoteClient;

private:
    /// The minimum number of players to start the game
    std::size_t _minPlayers = 1;
    /// The maximum number of players that can join the lobby
    std::size_t _maxPlayers;
    /// The random device used to generate player hashes
    std::random_device _random;
    /// The distribution used to generate player hashes
    std::uniform_int_distribution<size_t> _dist;
};
}

#endif /* !RTYPE_NETWORKING_LOBBY_HPP */
