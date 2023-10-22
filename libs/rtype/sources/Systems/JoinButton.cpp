/*
** EPITECH PROJECT, 2023
** engine
** File description:
** Join Button System
*/

#include "Systems/JoinButton.hpp"
#include "Components/Focusable.hpp"
#include "Components/Text.hpp"
#include "Game.hpp"
#include "LobbyClientImpl.hpp"
#include "Registry.hpp"
#include <iostream>

System::JoinButton::JoinButton(
    RTypeLobby &game, engine::Registry &registry, engine::Entity &button,
    engine::Entity &address, engine::Entity &port, engine::Entity &name
)
    : _game(game)
    , _registry(registry)
    , _button(button)
    , _address(address)
    , _port(port)
    , _name(name)
{
}

void System::JoinButton::operator()()
{
    auto &focusable = _registry.get_components<Component::Focusable>()[_button];

    if (not focusable or not focusable->isFocused)
        return;

    auto &address = _registry.get_components<Component::Text>()[_address];
    auto &port = _registry.get_components<Component::Text>()[_port];
    auto &name = _registry.get_components<Component::Text>()[_name];

    focusable->isFocused = false;

    std::cout << "Joining " << address->_text << ":" << port->_text << " as "
              << name->_text << std::endl;
    LobbyClientImpl &client
        = dynamic_cast<LobbyClientImpl &>(_registry.add_system<LobbyClientImpl>(
            _game, _registry, address->_text, std::stoi(port->_text)
        ));
    _registry.reset_scene();
    // TODO: add loading screen
    client.sendJoinRequest(name->_text);
}
