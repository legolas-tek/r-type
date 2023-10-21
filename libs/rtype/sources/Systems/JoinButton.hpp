/*
** EPITECH PROJECT, 2023
** engine
** File description:
** Join Button
*/

#ifndef RTYPE_MENU_JOIN_BUTTON_HPP_
#define RTYPE_MENU_JOIN_BUTTON_HPP_

#include "Entity.hpp"
#include "Game.hpp"
#include "ISystem.hpp"
#include "Registry.hpp"

namespace System {

/// @brief This system checks if the button is pressed, and if it is, it
/// requests to start the game
class JoinButton : public ISystem {

public:
    JoinButton(
        RTypeLobby &game, engine::Registry &registry, engine::Entity &button,
        engine::Entity &address, engine::Entity &port, engine::Entity &name
    );

    void operator()() override;

private:
    RTypeLobby &_game;
    engine::Registry &_registry;
    engine::Entity &_button;
    engine::Entity &_address;
    engine::Entity &_port;
    engine::Entity &_name;
};
}

#endif /* !RTYPE_MENU_JOIN_BUTTON_HPP_ */
