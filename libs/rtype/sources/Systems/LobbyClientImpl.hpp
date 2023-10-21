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

/// @brief This system implements the lobby client
class LobbyClientImpl : public net::LobbyClient {
public:
    LobbyClientImpl(
        RTypeLobby &game, std::string const &addr, std::size_t port
    );

private:
    void
    onJoinSuccess(std::uint8_t playerNumber, std::uint64_t playerHash) override;
    void
    onNewPlayer(std::uint8_t playerNumber, std::string &&playerName) override;
    void onGameStart() override;
    void onError(std::string &&errorMessage) override;

private:
    RTypeLobby &_game;
};
}

#endif /* !RTYPE_MENU_JOIN_BUTTON_HPP_ */
