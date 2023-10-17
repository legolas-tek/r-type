/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** Lobby implementation
*/

#include "Lobby.hpp"
#include <string>

net::lobby::RemoteClient::RemoteClient(
    manager::TcpConnection &&network, Lobby &parent
)
    : LobbyRemoteClient(std::move(network))
    , _parent(parent)
{
}

void net::lobby::RemoteClient::onJoinRequest(std::string &&playerName)
{
    _playerName = std::move(playerName);
    if (_parent._maxPlayers == _parent._players.size()) {
        sendError("Lobby is full!");
        return;
    }
    _parent._players.push_back(this);
    _playerNumber = _parent._players.size();
    _playerHash = _parent._dist(_parent._random);
    sendJoinSuccess(_playerNumber, _playerHash);
    for (auto &player : _parent._players) {
        player->sendNewPlayer(_playerNumber, _playerName);
    }
}

void net::lobby::RemoteClient::onStartRequest()
{
    for (auto &player : _parent._players) {
        player->sendGameStart();
    }
}

net::lobby::Lobby::Lobby(std::size_t port, std::size_t maxPlayers)
    : LobbyServer(port)
    , _maxPlayers(maxPlayers)
{
}

void net::lobby::Lobby::emplaceClient(manager::TcpConnection &&connection)
{
    _clients.emplace_back(std::move(connection), *this);
}
