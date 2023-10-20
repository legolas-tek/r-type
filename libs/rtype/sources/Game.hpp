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
/// @brief The Width of the ship sprite
static inline constexpr int SHIP_W = 32;
/// @brief The Height of the ship sprite
static inline constexpr int SHIP_H = 14;
/// @brief The number of frames for the ship animation
static inline constexpr int SHIP_F = 4;
/// @brief The index to find the ship sprite
static inline constexpr int SHIP_I = 3;

/// @brief The Width of the basic ennemy sprite
static inline constexpr int BASIC_ENNEMY_W = 32;
/// @brief The Height of the basic ennemy sprite
static inline constexpr int BASIC_ENNEMY_H = 32;
/// @brief The number of frames for the basic ennemy animation
static inline constexpr int BASIC_ENNEMY_F = 4;
/// @brief The index to find the basic ennemy sprite
static inline constexpr int BASIC_ENNEMY_I = 6;

/// @brief The Width of the shooting ennemy sprite
static inline constexpr int SHOOT_ENNEMY_W = 62;
/// @brief The Height of the shooting ennemy sprite
static inline constexpr int SHOOT_ENNEMY_H = 47;
/// @brief The number of frames for the shoot ennemy animation
static inline constexpr int SHOOT_ENNEMY_F = 4;
/// @brief The index to find the shoot ennemy sprite
static inline constexpr int SHOOT_ENNEMY_I = 7;

/// @brief The Width of the borders sprite
static inline constexpr int BORDERS_W = 960;
/// @brief The Height of the borders sprite
static inline constexpr int BORDERS_H = 8;
/// @brief The number of frames for the borders animation
static inline constexpr int BORDERS_F = 2;
/// @brief The index to find the bottom border sprite
static inline constexpr int BOT_BORDER_I = 8;
/// @brief The index to find the top border sprite
static inline constexpr int TOP_BORDER_I = 9;

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
