/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game
*/

#include "Game.hpp"

#include "Components/Drawable.hpp"
#include "Components/Position.hpp"

#include "Key.hpp"
#include "Lobby.hpp"
#include "Registry.hpp"
#include "Rendering.hpp"

void RTypeLobby::registerAllComponents(engine::Registry &reg)
{
    reg.register_component<Component::Position>();
    reg.register_component<Component::Drawable>();
}

void RTypeLobby::registerAdditionalClientSystems(engine::Registry &reg)
{
    reg.add_system<rendering::system::Rendering>(reg);
}

void RTypeLobby::registerAdditionalServerSystems(engine::Registry &reg)
{
    _serverLobby = dynamic_cast<net::lobby::Lobby &>(
        reg.add_system<net::lobby::Lobby>(4242, 4)
    );
}

RTypeLobby::RTypeLobby(RTypeGame &game)
    : _game(game)
{
}

RTypeLobby::~RTypeLobby()
{
    _game._playerHash = _playerHash;
    _game._playerNumber = _playerNumber;
    if (_serverLobby)
        _game._serverClients = std::move(_serverLobby->get().getClients());
}
