/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** Lobby implementation
*/

#include "Lobby.hpp"
#include "IGame.hpp"

#include <iostream>

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
    std::size_t playerCount = _parent.getCurrentPlayerCount();
    if (_parent._maxPlayers == playerCount) {
        sendError("Lobby is full!");
        return;
    }
    _playerNumber = playerCount + 1;
    _playerHash = _parent._dist(_parent._random);
    std::cout << "Player " << _playerName << " joined the lobby as player "
              << _playerNumber << " with hash " << _playerHash << std::endl;
    sendJoinSuccess(_playerNumber, _playerHash);
    for (auto &player : _parent._clients) {
        if (!player._playerNumber)
            continue;
        player.sendNewPlayer(_playerNumber, _playerName);
        if (player._playerNumber != _playerNumber) {
            sendNewPlayer(player._playerNumber, player._playerName);
        }
    }
}

void net::lobby::RemoteClient::onStartRequest()
{
    std::cout << "Player " << _playerName << " requested to start the game"
              << std::endl;
    for (auto &player : _parent._clients) {
        if (player._playerNumber) {
            player.sendGameStart();
        }
    }
    throw engine::IGame::StartGameException();
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

std::size_t net::lobby::Lobby::getCurrentPlayerCount() const
{
    std::size_t count = 0;

    for (auto &player : _clients) {
        if (player._playerNumber) {
            count++;
        }
    }
    return count;
}

std::string const &net::lobby::RemoteClient::getPlayerName() const
{
    return _playerName;
}

size_t net::lobby::RemoteClient::getPlayerNumber() const
{
    return _playerNumber;
}

size_t net::lobby::RemoteClient::getPlayerHash() const
{
    return _playerHash;
}
