/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game
*/

#include "Game.hpp"

#include "Components/Animation.hpp"
#include "Components/Drawable.hpp"
#include "Components/Focusable.hpp"
#include "Components/HitBox.hpp"
#include "Components/Position.hpp"
#include "Components/Text.hpp"

#include "Systems/Editable.hpp"
#include "Systems/Focusable.hpp"
#include "Systems/Text.hpp"

#include "Rendering.hpp"

void RTypeLobby::registerAllComponents(engine::Registry &reg)
{
    reg.register_component<Component::Position>();
    reg.register_component<Component::Drawable>();
    reg.register_component<Component::Animation>();
    reg.register_component<Component::Text>();
    reg.register_component<Component::Focusable>();
    reg.register_component<Component::HitBox>();
    reg.register_component<Component::Editable>();
}

void RTypeLobby::registerAdditionalClientSystems(engine::Registry &reg)
{
    reg.add_system<rendering::system::Rendering>(reg);
    reg.add_system<rendering::system::Focusable>(
        reg.get_components<Component::Focusable>(),
        reg.get_components<Component::HitBox>(),
        reg.get_components<Component::Position>()
    );
    reg.add_system<rendering::system::Editable>(
        reg.get_components<Component::Editable>(),
        reg.get_components<Component::Focusable>(),
        reg.get_components<Component::Text>()
    );
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

void RTypeLobby::registerAdditionalSystems(engine::Registry &reg)
{
}

void RTypeLobby::initAssets(engine::Registry &reg)
{
}

void RTypeLobby::initScene(engine::Registry &reg)
{
    engine::Entity Title(reg.get_new_entity());

    reg.get_components<Component::Position>().emplace_at(
        Title, Component::Position(0, 0)
    );
    reg.get_components<Component::Text>().insert_at(
        Title,
        Component::Text(
            "R-Type", "./client/assets/fonts/Over_There.ttf", 50, 10
        )
    );
    reg.get_components<Component::Focusable>().emplace_at(
        Title, Component::Focusable(false)
    );
    reg.get_components<Component::Editable>().emplace_at(
        Title, Component::Editable()
    );
    reg.get_components<Component::HitBox>().insert_at(
        Title, Component::HitBox(300, 300)
    );
}
