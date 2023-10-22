/*
** EPITECH PROJECT, 2023
** engine
** File description:
** Lobby Client Implementation
*/

#include "LobbyClientImpl.hpp"
#include "Components/Position.hpp"
#include "Components/Text.hpp"
#include "Entity.hpp"
#include "Game.hpp"
#include <iostream>

System::LobbyClientImpl::LobbyClientImpl(
    RTypeLobby &game, engine::Registry &reg, std::string const &addr,
    std::size_t port
)
    : net::LobbyClient(addr, port)
    , _game(game)
    , _registry(reg)
{
}

void System::LobbyClientImpl::onJoinSuccess(
    std::uint8_t playerNumber, std::uint64_t playerHash
)
{
    std::cout << "Join success: " << int(playerNumber) << " " << playerHash
              << std::endl;
    _game.onJoinSuccess(playerNumber, playerHash);
    _game.initLobbyScene(_registry, *this);
}

void System::LobbyClientImpl::onNewPlayer(
    std::uint8_t playerNumber, std::string &&playerName
)
{
    std::cout << "New player: " << int(playerNumber) << " " << playerName
              << std::endl;
    engine::Entity player(_registry.get_new_entity());

    _registry.get_components<Component::Position>().emplace_at(
        player, Component::Position(25 + 150 * playerNumber, 100)
    );
    _registry.get_components<Component::Text>().emplace_at(
        player,
        Component::Text(
            std::move(playerName), "./assets/fonts/Over_There.ttf", 20, 5
        )
    );
}

void System::LobbyClientImpl::onGameStart()
{
    throw engine::IGame::StartGameException();
}

void System::LobbyClientImpl::onError(std::string &&error)
{
    std::cout << "Error: " << error << std::endl;
}
