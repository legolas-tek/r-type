/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game
*/

#include "Game.hpp"

#include "Components/Drawable.hpp"
#include "Components/Focusable.hpp"
#include "Components/HitBox.hpp"
#include "Components/Position.hpp"

#include "Systems/Focusable.hpp"

#include "Rendering.hpp"

void RTypeLobby::registerAllComponents(engine::Registry &reg)
{
    reg.register_component<Component::Position>();
    reg.register_component<Component::Drawable>();
    reg.register_component<Component::Focusable>();
    reg.register_component<Component::HitBox>();
}

void RTypeLobby::registerAdditionalClientSystems(engine::Registry &reg)
{
    reg.add_system<rendering::system::Rendering>(reg);
    reg.add_system<rendering::system::Focusable>(
        reg.get_components<Component::Focusable>(),
        reg.get_components<Component::HitBox>(),
        reg.get_components<Component::Position>()
    );
}

void RTypeLobby::registerAdditionalServerSystems(engine::Registry &reg)
{
    _serverLobby = dynamic_cast<net::lobby::Lobby &>(
        reg.add_system<net::lobby::Lobby>(4242, 4)
    );
}
