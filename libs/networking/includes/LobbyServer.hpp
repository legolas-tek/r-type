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

class LobbyRemoteClient : public ISystem {
public:
    LobbyRemoteClient(std::unique_ptr<manager::Tcp> &&network)
        : _network(std::move(network))
    {
    }

    void sendJoinSuccess(std::uint8_t playerNumber, std::uint64_t playerHash);
    void
    sendNewPlayer(std::uint8_t playerNumber, std::string const &playerName);
    void sendGameStart();
    void sendError(std::string const &errorMessage);

    void operator()() override;

private:
    void parsePacket();

private:
    virtual void onJoinRequest(std::string &&playerName) = 0;
    virtual void onStartRequest() = 0;

private:
    std::unique_ptr<net::manager::Tcp> _network;
};

template <typename RemoteClient> class LobbyServer : public ISystem {
public:
    LobbyServer(std::size_t port)
        : _server(port)
    {
    }

    void sendNewPlayer(std::uint8_t playerNumber, std::string const &playerName)
    {
        for (auto &client : _clients) {
            client.sendNewPlayer(playerNumber, playerName);
        }
    }

    void sendGameStart()
    {
        for (auto &client : _clients) {
            client.sendGameStart();
        }
    }

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
    std::vector<RemoteClient> _clients;
    manager::TcpServer _server;
};
}

#endif /* !RTYPE_NETWORKING_LOBBY_SERVER_HPP */
