/*
** EPITECH PROJECT, 2023
** R-Type game
** File description:
** Join as Spectator Button
*/

#ifndef RTYPE_MENU_SPECTATE_BUTTON_HPP_
#define RTYPE_MENU_SPECTATE_BUTTON_HPP_

#include "Entity.hpp"
#include "Game.hpp"
#include "ISystem.hpp"
#include "Registry.hpp"

namespace System {

/**
 * @brief The system that handles click on the spectate button
 *
 * When the user clicks on the join button, this system will get the address and
 * port from the input fields and try to connect to the server, and
 * join the lobby as spectator.
 */
class SpectateButton : public ISystem {

public:
    /**
     * @brief Construct a new Spectate Button system
     *
     * @param game The game instance
     * @param registry The registry of the game
     * @param button The entity of the button
     * @param address The entity of the address input field
     * @param port The entity of the port input field
     */
    SpectateButton(
        RTypeLobby &game, engine::Registry &registry, engine::Entity &button,
        engine::Entity &address, engine::Entity &port
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
};
}

#endif /* !RTYPE_MENU_SPECTATE_BUTTON_HPP_ */
