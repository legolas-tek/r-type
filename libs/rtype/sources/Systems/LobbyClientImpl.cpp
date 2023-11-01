/*
** EPITECH PROJECT, 2023
** engine
** File description:
** Lobby Client Implementation
*/

#include "LobbyClientImpl.hpp"
#include "Components/Animation.hpp"
#include "Components/Drawable.hpp"
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
    , _address(addr)
    , _port(port)
{
}

void System::LobbyClientImpl::onJoinSuccess(
    std::uint8_t playerNumber, std::uint64_t playerHash
)
{
    std::cout << "Join success: " << int(playerNumber) << " " << playerHash
              << std::endl;
    _game.onJoinSuccess(playerNumber, playerHash, std::move(_address), _port);
    _game.initLobbyScene(_registry, *this);
}

void System::LobbyClientImpl::onNewPlayer(
    std::uint8_t playerNumber, std::string &&playerName
)
{
    auto SHIP_F = RTypeGame::SHIP_F;
    auto SHIP_H = RTypeGame::SHIP_H;
    auto SHIP_W = RTypeGame::SHIP_W;

    std::cout << "New player: " << int(playerNumber) << " " << playerName
              << std::endl;
    engine::Entity nameEntity(_registry.get_new_entity());

    _registry.get_components<Component::Position>().insert_at(
        nameEntity, Component::Position(25 + 150 * playerNumber, 200)
    );
    _registry.get_components<Component::Text>().insert_at(
        nameEntity,
        Component::Text(
            std::move(playerName), "./assets/fonts/Over_There.ttf", 15, 5
        )
    );
    engine::Entity iconEntity(_registry.get_new_entity());

    _registry.get_components<Component::Position>().insert_at(
        iconEntity, Component::Position(25 + 150 * playerNumber, 100)
    );
    _registry.get_components<Component::Drawable>().insert_at(
        iconEntity,
        Component::Drawable(0, SHIP_W, SHIP_H, 3, 17 * (playerNumber - 1))
    );
    _registry.get_components<Component::Animation>().insert_at(
        iconEntity,
        Component::Animation(
            SHIP_W * SHIP_F, SHIP_H, SHIP_W, SHIP_H, SHIP_W, 50
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
