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

/**
 * @brief The system that handles click on the join button
 *
 * When the user clicks on the join button, this system will get the address,
 * port and name from the input fields and try to connect to the server, and
 * join the lobby under the given name.
 */
class JoinButton : public ISystem {

public:
    /**
     * @brief Construct a new Join Button system
     *
     * @param game The game instance
     * @param registry The registry of the game
     * @param button The entity of the button
     * @param address The entity of the address input field
     * @param port The entity of the port input field
     * @param name The entity of the name input field
     */
    JoinButton(
        RTypeLobby &game, engine::Registry &registry, engine::Entity &button,
        engine::Entity &address, engine::Entity &port, engine::Entity &name
    );

    /// Runs the check
    void operator()() override;

private:
    /// The game instance
    RTypeLobby &_game;
    /// The registry of the game
    engine::Registry &_registry;
    /// The entity of the button
    engine::Entity &_button;
    /// The entity of the address input field
    engine::Entity &_address;
    /// The entity of the port input field
    engine::Entity &_port;
    /// The entity of the player name input field
    engine::Entity &_name;
};
}

#endif /* !RTYPE_MENU_JOIN_BUTTON_HPP_ */
