/*
** EPITECH PROJECT, 2023
** engine
** File description:
** Lobby Client Implementation
*/

#include "LobbyClientImpl.hpp"
#include "Game.hpp"
#include <iostream>

System::LobbyClientImpl::LobbyClientImpl(
    RTypeLobby &game, std::string const &addr, std::size_t port
)
    : net::LobbyClient(addr, port)
    , _game(game)
{
}

void System::LobbyClientImpl::onJoinSuccess(
    std::uint8_t playerNumber, std::uint64_t playerHash
)
{
    std::cout << "Join success: " << int(playerNumber) << " " << playerHash
              << std::endl;
    _game.onJoinSuccess(playerNumber, playerHash);
}

void System::LobbyClientImpl::onNewPlayer(
    std::uint8_t playerNumber, std::string &&playerName
)
{
    std::cout << "New player: " << int(playerNumber) << " " << playerName
              << std::endl;
}

void System::LobbyClientImpl::onGameStart()
{
    throw engine::IGame::StartGameException();
}

void System::LobbyClientImpl::onError(std::string &&error)
{
    std::cout << "Error: " << error << std::endl;
}
