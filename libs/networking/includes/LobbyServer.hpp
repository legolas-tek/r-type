/*
** EPITECH PROJECT, 2023
** RType Networking
** File description:
** Lobby protocol
*/

#ifndef RTYPE_NETWORKING_LOBBY_SERVER_HPP
#define RTYPE_NETWORKING_LOBBY_SERVER_HPP

#include "ISystem.hpp"
#include "TcpServer.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace net {

namespace manager {
class Tcp;
}

/**
 * @brief The lobby remote client, which represents a connection to an online
 * lobby client
 *
 * This class contains functions to interact with the remote lobby client, over
 * a tcp connection. This is a System, but it is designed to work as a subsystem
 * of the LobbyServer system.
 *
 * It is an abstract class, so it must be inherited from to implement the logic
 * for the incoming packets.
 */
class LobbyRemoteClient : public ISystem {
public:
    /**
     * @brief Construct a new Lobby Remote Client object
     *
     * @param network The network connection to use
     */
    LobbyRemoteClient(std::unique_ptr<manager::Tcp> &&network);

    /// Send a join success packet to the client
    void sendJoinSuccess(std::uint8_t playerNumber, std::uint64_t playerHash);
    /// Send a New Player notification to the client
    void
    sendNewPlayer(std::uint8_t playerNumber, std::string const &playerName);
    /// Send a Game Start notification to the client
    void sendGameStart();
    /// Send an error message to the client
    void sendError(std::string const &errorMessage);

    /// Checks for incoming packets from the client and handles them
    void operator()() override;

private:
    /// Parses an incoming packet
    void parsePacket();

private:
    /// Called when the client sends a join request
    virtual void onJoinRequest(std::string &&playerName) = 0;
    /// Called when the client sends a start request
    virtual void onStartRequest() = 0;

private:
    /// The underlying tcp connection
    std::unique_ptr<net::manager::Tcp> _network;
};

/**
 * @brief The lobby server, which uses a tcp server to accept new connections
 *
 * This class contains functions to interact with the remote lobby clients, over
 * tcp connections. This is a System, so it must be added to a Registry.
 *
 * @tparam RemoteClient The type of remote client, which must inherit from
 * net::LobbyRemoteClient
 */
template <typename RemoteClient> class LobbyServer : public ISystem {
public:
    /**
     * @brief Construct a new Lobby Server object
     *
     * @param port The port to listen on
     */
    LobbyServer(std::size_t port)
        : _server(port)
    {
    }

    /**
     * @brief Send a New Player notification to all clients
     *
     * @param playerNumber The player number of the new player
     * @param playerName The name of the new player
     */
    void sendNewPlayer(std::uint8_t playerNumber, std::string const &playerName)
    {
        for (auto &client : _clients) {
            client.sendNewPlayer(playerNumber, playerName);
        }
    }

    /**
     * @brief Send a Game Start notification to all clients
     */
    void sendGameStart()
    {
        for (auto &client : _clients) {
            client.sendGameStart();
        }
    }

    /// Checks for new connections and incoming packets from the clients
    void operator()() override
    {
        auto client = _server.acceptNewClient();
        if (client) {
            _clients.emplace_back(std::move(client));
        }
        for (auto &client : _clients) {
            client();
        }
    }

private:
    /// The list of connected clients
    std::vector<RemoteClient> _clients;
    /// The underlying tcp server
    manager::TcpServer _server;
};
}

#endif /* !RTYPE_NETWORKING_LOBBY_SERVER_HPP */
