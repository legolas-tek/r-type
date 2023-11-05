/*
** EPITECH PROJECT, 2023
** R-Type Game
** File description:
** Join as Spectator Button System
*/

#include "Systems/SpectateButton.hpp"
#include "Components/Focusable.hpp"
#include "Components/Text.hpp"
#include "Game.hpp"
#include "LobbyClientImpl.hpp"
#include "Registry.hpp"

#include <iostream>

System::SpectateButton::SpectateButton(
    RTypeLobby &game, engine::Registry &registry, engine::Entity &button,
    engine::Entity &address, engine::Entity &port
)
    : _game(game)
    , _registry(registry)
    , _button(button)
    , _address(address)
    , _port(port)
{
}

void System::SpectateButton::operator()()
{
    auto &focusable = _registry.get_components<Component::Focusable>()[_button];

    if (not focusable or not focusable->isFocused)
        return;

    auto &address = _registry.get_components<Component::Text>()[_address];
    auto &port = _registry.get_components<Component::Text>()[_port];

    focusable->isFocused = false;

    std::cout << "Joining " << address->_text << ":" << port->_text
              << " as spectator" << std::endl;
    LobbyClientImpl &client
        = dynamic_cast<LobbyClientImpl &>(_registry.add_system<LobbyClientImpl>(
            _game, _registry, address->_text, std::stoi(port->_text)
        ));
    client.sendSpectateRequest();
    _registry.reset_scene();
    // TODO: add loading screen
}
