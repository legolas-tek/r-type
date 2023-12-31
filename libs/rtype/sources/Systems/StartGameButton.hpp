/*
** EPITECH PROJECT, 2023
** engine
** File description:
** Start Game Button
*/

#ifndef RTYPE_MENU_START_GAME_BUTTON_HPP_
#define RTYPE_MENU_START_GAME_BUTTON_HPP_

#include "Components/Focusable.hpp"
#include "Entity.hpp"
#include "Game.hpp"
#include "ISystem.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"

namespace System {

/**
 * @brief The system that handles click on the start game button
 *
 * When the user clicks on the start game button, this system will send a
 * request to the server to start the game.
 */
class StartGameButton : public ISystem {

public:
    /**
     * @brief Construct a new Start Game Button object
     *
     * @param client The lobby client instance
     * @param button The button entity
     */
    StartGameButton(LobbyClientImpl &client, Component::Focusable &focusable);

    /// Runs the check
    void operator()() override;

private:
    /// The lobby client instance
    LobbyClientImpl &_client;
    /// The focusable component of the button
    Component::Focusable &_focusable;
};
}

#endif /* !RTYPE_MENU_JOIN_BUTTON_HPP_ */
