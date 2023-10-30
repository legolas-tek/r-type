/*
** EPITECH PROJECT, 2023
** engine
** File description:
** Lobby CLient Impl
*/

#ifndef RTYPE_LOBBY_CLIENT_IMPL_HPP_
#define RTYPE_LOBBY_CLIENT_IMPL_HPP_

#include "Entity.hpp"
#include "Game.hpp"
#include "ISystem.hpp"
#include "LobbyClient.hpp"
#include "Registry.hpp"

namespace System {

/**
 * @brief The implementation of the lobby client
 *
 * Implementation of the lobby client, it will be used to communicate with the
 * server during the lobby phase. It acts as a system and receives events from
 * the server.
 *
 * It is created by the JoinButton system, after the user has entered the server
 * address and port, and destroyed when the user leaves the lobby.
 */
class LobbyClientImpl : public net::LobbyClient {
public:
    /**
     * @brief Construct a new Lobby Client Impl object
     *
     * @param game The game object
     * @param addr The server address
     * @param port The server port
     */
    LobbyClientImpl(
        RTypeLobby &game, engine::Registry &reg, std::string const &addr,
        std::size_t port
    );

private:
    /// When the user successfully joins the lobby, send the information to the
    /// game object so it can be used by the game later
    void
    onJoinSuccess(std::uint8_t playerNumber, std::uint64_t playerHash) override;
    /// When a new player joins the lobby, show it in the lobby
    void
    onNewPlayer(std::uint8_t playerNumber, std::string &&playerName) override;
    /// When the game starts, throw an event to start the game
    void onGameStart() override;
    /// When an error occurs, show it
    void onError(std::string &&errorMessage) override;

private:
    /// The game object
    RTypeLobby &_game;
    /// The registry of the game
    engine::Registry &_registry;

    /// The server address
    std::string _address;
    /// The server port
    std::size_t _port;
};
}

#endif /* !RTYPE_MENU_JOIN_BUTTON_HPP_ */
