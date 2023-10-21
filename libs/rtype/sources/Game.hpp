/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game
*/

#ifndef R_TYPE_GAME_HPP
#define R_TYPE_GAME_HPP

#include "IGame.hpp"
#include "Lobby.hpp"
#include <functional>
#include <memory>

class RTypeGame : public engine::IGame {
public:
    void registerAllComponents(engine::Registry &reg) override;

    void registerAdditionalServerSystems(engine::Registry &reg) override;
    void registerAdditionalClientSystems(engine::Registry &reg) override;
    void registerAdditionalSystems(engine::Registry &reg) override;

    void initAssets(engine::Registry &reg) override;
    void initScene(engine::Registry &reg) override;

    std::unique_ptr<engine::IGame> createLobby() override;
};

class RTypeLobby : public engine::IGame {
public:
    void registerAllComponents(engine::Registry &reg) override;

    void registerAdditionalServerSystems(engine::Registry &reg) override;
    void registerAdditionalClientSystems(engine::Registry &reg) override;

private:
    /// Server side, contains the lobby, null on client
    std::optional<std::reference_wrapper<net::lobby::Lobby>> _serverLobby;

private:
    /// Client side, contains the player number (1-4), 0 on server
    std::size_t _playerNumber = 0;
    /// Client side, contains the player hash, 0 on server
    std::size_t _playerHash = 0;
};

#endif /*! R_TYPE_GAME_HPP */
