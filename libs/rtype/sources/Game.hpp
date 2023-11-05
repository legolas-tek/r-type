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
#include "ScoreManager.hpp"
#include <functional>
#include <memory>
#include <optional>

namespace System {
class LobbyClientImpl;
}

class RTypeGame : public engine::IGame {
public:
    /// @brief The Width of the ship sprite
    static inline constexpr int SHIP_W = 32;
    /// @brief The Height of the ship sprite
    static inline constexpr int SHIP_H = 14;
    /// @brief The number of frames for the ship animation
    static inline constexpr int SHIP_F = 4;
    /// @brief The index to find the ship sprite
    static inline constexpr int SHIP_I = 3;
    /// @brief The Health a ship should have
    static inline constexpr int SHIP_HEALTH = 3;

    /// @brief The Width of the basic ennemy sprite
    static inline constexpr int BASIC_ENNEMY_W = 32;
    /// @brief The Height of the basic ennemy sprite
    static inline constexpr int BASIC_ENNEMY_H = 32;
    /// @brief The number of frames for the basic ennemy animation
    static inline constexpr int BASIC_ENNEMY_F = 4;
    /// @brief The index to find the basic ennemy sprite
    static inline constexpr int BASIC_ENNEMY_I = 6;
    /// @brief The Health a basic enemy should have
    static inline constexpr int BASIC_ENNEMY_HEALTH = 1;

    /// @brief The Width of the shooting ennemy sprite
    static inline constexpr int SHOOT_ENNEMY_W = 62;
    /// @brief The Height of the shooting ennemy sprite
    static inline constexpr int SHOOT_ENNEMY_H = 47;
    /// @brief The number of frames for the shoot ennemy animation
    static inline constexpr int SHOOT_ENNEMY_F = 4;
    /// @brief The index to find the shoot ennemy sprite
    static inline constexpr int SHOOT_ENNEMY_I = 7;
    /// @brief The Health a shoot enemy should have
    static inline constexpr int SHOOT_ENNEMY_HEALTH = 3;

    /// @brief The Width of the first boss sprite
    static inline constexpr int FIRST_BOSS_W = 162;
    /// @brief The Height of the first boss sprite
    static inline constexpr int FIRST_BOSS_H = 207;
    /// @brief The number of frames for the first boss animation
    static inline constexpr int FIRST_BOSS_F = 3;
    /// @brief The index to find the first boss sprite
    static inline constexpr int FIRST_BOSS_I = 13;
    /// @brief The Health a first boss should have
    static inline constexpr int FIRST_BOSS_HEALTH = 20;

    /// @brief The Width of the small turret sprite
    static inline constexpr int SMALL_TURRET_W = 32;
    /// @brief The Height of the small turret sprite
    static inline constexpr int SMALL_TURRET_H = 15;
    /// @brief The index to find the small turret sprite
    static inline constexpr int SMALL_TURRET_I = 12;

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

    void registerAllComponents(engine::Registry &reg) override;

    void registerAdditionalServerSystems(engine::Registry &reg) override;
    void registerAdditionalClientSystems(engine::Registry &reg) override;
    void registerAdditionalSystems(engine::Registry &reg) override;

    void initAssets(engine::Registry &reg) override;
    void initScene(engine::Registry &reg) override;

public:
    /// Server side, contains the clients, empty on client
    std::vector<net::lobby::RemoteClient> _serverClients;
    /// Server side, contains the score manager, nullopt on client
    std::optional<ScoreManager> _scoreManager;

public:
    /// Client side, contains the player number (1-4), 0 on server
    std::size_t _playerNumber = 0;
    /// Client side, contains our player hash, 0 on server
    std::size_t _playerHash = 0;
    /// Client side, contains the server address to connect to
    std::string _address;
    /// Client side, contains the server port to use
    std::size_t _port;
};

class RTypeLobby : public engine::IGame {
public:
    void registerAllComponents(engine::Registry &reg) override;

    void registerAdditionalServerSystems(engine::Registry &reg) override;
    void registerAdditionalClientSystems(engine::Registry &reg) override;
    void registerAdditionalSystems(engine::Registry &reg) override;

    void initAssets(engine::Registry &reg) override;
    /// Init the initial scene, which is the menu
    void initScene(engine::Registry &reg) override;
    /// Init the lobby scene, which is where other players are displayed
    void initLobbyScene(engine::Registry &reg, System::LobbyClientImpl &client);

    void onJoinSuccess(
        std::uint8_t playerNumber, std::uint64_t playerHash,
        std::string address, std::size_t port
    );

    std::unique_ptr<engine::IGame> createNextGame() override;

    bool isClientScene() const override
    {
        return true;
    }

private:
    engine::Entity _joinButton { 0 };
    engine::Entity _spectateButton { 0 };
    engine::Entity _addressInput { 0 };
    engine::Entity _portInput { 0 };
    engine::Entity _nameInput { 0 };

private:
    /// Server side, contains the lobby, null on client
    std::optional<std::reference_wrapper<net::lobby::Lobby>> _serverLobby;

private:
    /// Client side, contains the player number (1-4), 0 on server
    std::size_t _playerNumber = 0;
    /// Client side, contains the player hash, 0 on server
    std::size_t _playerHash = 0;
    /// Client side, contains the server address to connect to
    std::string _address;
    /// Client side, contains the server port to use
    std::size_t _port;
};

#endif /*! R_TYPE_GAME_HPP */
