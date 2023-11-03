/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game
*/

#include "DiffLogger.hpp"
#include "Game.hpp"

#include "Components/Solid.hpp"
#include "Components/Text.hpp"

#include "Systems/AnimationSystem.hpp"
#include "Systems/AttackSystem.hpp"
#include "Systems/CollisionsSystem.hpp"
#include "Systems/DamageSystem.hpp"
#include "Systems/DeathAnimationManager.hpp"
#include "Systems/DeathSystem.hpp"
#include "Systems/FollowSystem.hpp"
#include "Systems/LifeTimeSystem.hpp"
#include "Systems/MoveSystem.hpp"
#include "Systems/NetworkSystem.hpp"
#include "Systems/RespawnSystem.hpp"
#include "Systems/SoundManagerSystem.hpp"
#include "Systems/SpawnEnemySystem.hpp"
#include "Systems/WaveManagerSystem.hpp"
#include "Systems/FloatingSystem.hpp"

#include "Key.hpp"
#include "NetworkClientSystem.hpp"
#include "Rendering.hpp"

void RTypeGame::registerAllComponents(engine::Registry &reg)
{
    reg.register_component<Component::Position>();
    reg.register_component<Component::Velocity>();
    reg.register_component<Component::Drawable>();
    reg.register_component<Component::Controllable>();
    reg.register_component<Component::Collision>();
    reg.register_component<Component::Animation>();
    reg.register_component<Component::HitBox>();
    reg.register_component<Component::FireRate>();
    reg.register_component<Component::LifeTime>();
    reg.register_component<Component::Damage>();
    reg.register_component<Component::Health>();
    reg.register_component<Component::Life>();
    reg.register_component<Component::Follow>();
    reg.register_component<Component::Text>();
    reg.register_component<Component::Solid>();
    reg.register_component<Component::Floating>();
}

void RTypeGame::registerAdditionalServerSystems(engine::Registry &reg)
{
    reg.add_system<System::CollisionsSystem>(
        reg.get_components<Component::Position>(),
        reg.get_components<Component::HitBox>(),
        reg.get_components<Component::Collision>()
    );
    reg.add_system<System::AttackSystem>(
        reg.get_components<Component::FireRate>(),
        reg.get_components<Component::Health>(),
        reg.get_components<Component::Position>(), reg
    );
    reg.add_system<System::LifeTimeSystem>(
        reg.get_components<Component::LifeTime>(), reg
    );
    reg.add_system<System::DamageSystem>(
        reg.get_components<Component::Damage>(),
        reg.get_components<Component::Health>(),
        reg.get_components<Component::Collision>(), reg
    );
    reg.add_system<System::DeathAnimationManager>(
        reg.get_components<Component::Position>(),
        reg.get_components<Component::Health>(),
        reg.get_components<Component::Collision>(),
        reg.get_components<Component::Damage>(),
        reg.get_components<Component::Controllable>(), reg
    );
    reg.add_system<System::RespawnSystem>(
        reg.get_components<Component::Life>(),
        reg.get_components<Component::Health>(),
        reg.get_components<Component::Controllable>(),
        reg.get_components<Component::Drawable>(),
        reg.get_components<Component::Velocity>(),
        reg.get_components<Component::Collision>(),
        reg.get_components<Component::HitBox>(), reg
    );
    reg.add_system<System::DeathSystem>(
        reg.get_components<Component::Health>(),
        reg.get_components<Component::Life>(), reg
    );
    reg.add_system<System::WaveManagerSystem>(reg);
    reg.add_system<System::FloatingSystem>(
        reg.get_components<Component::Position>(),
        reg.get_components<Component::Velocity>(),
        reg.get_components<Component::Floating>()
    );
    reg.add_system<rtype::NetworkServerSystem>(reg, 4242, _serverClients);
}

void RTypeGame::registerAdditionalClientSystems(engine::Registry &reg)
{
    reg.add_system<System::SoundManagerSystem>(reg);
    reg.add_system<System::AnimationSystem>(reg);
    reg.add_system<rendering::system::Rendering>(reg);
    reg.add_system<rendering::system::Key>(
        reg.get_components<Component::Controllable>(),
        reg.get_components<Component::Velocity>(), _playerNumber
    );
    reg.add_system<net::system::NetworkClient>(
        reg, _address, _port, _playerNumber, _playerHash
    );
}

void RTypeGame::registerAdditionalSystems(engine::Registry &reg)
{
#ifdef DEBUG_LOG_DIFF
    reg.add_system<net::system::DiffLogger>(reg);
#endif
    reg.add_system<System::MoveSystem>(
        reg.get_components<Component::Position>(),
        reg.get_components<Component::Velocity>(),
        reg.get_components<Component::Solid>(),
        reg.get_components<Component::Collision>()
    );
    reg.add_system<System::FollowSystem>(
        reg.get_components<Component::Follow>(),
        reg.get_components<Component::Position>()
    );
}

void RTypeGame::initAssets(engine::Registry &reg)
{
    reg._assets_paths.emplace_back(
        "./assets/images/cyberpunk_street_background.png"
    );
    reg._assets_paths.emplace_back(
        "./assets/images/cyberpunk_street_midground.png"
    );
    reg._assets_paths.emplace_back(
        "./assets/images/cyberpunk_street_foreground.png"
    );
    reg._assets_paths.emplace_back("./assets/images/space_ships.png");
    reg._assets_paths.emplace_back("./assets/images/Plasma_Beam.png");
    reg._assets_paths.emplace_back("./assets/images/impact_explosion.png");
    reg._assets_paths.emplace_back("./assets/images/basic_ennemy.png");
    reg._assets_paths.emplace_back("./assets/images/shooting_ennemy.png");
    reg._assets_paths.emplace_back(
        "./assets/images/first_level_bottom_borders.png"
    );
    reg._assets_paths.emplace_back("./assets/images/first_level_top_borders.png"
    );
    reg._assets_paths.emplace_back("./assets/images/big_explosion.png");
    reg._assets_paths.emplace_back("./assets/images/small_turret.png");
    reg._assets_paths.emplace_back("./assets/images/first_boss.png");
}

void RTypeGame::initScene(engine::Registry &reg)
{
    engine::Entity background(reg.get_new_entity());
    engine::Entity midground(reg.get_new_entity());
    engine::Entity foreground(reg.get_new_entity());
    engine::Entity topBorder(reg.get_new_entity());
    engine::Entity bottomBorder(reg.get_new_entity());

    // ==================== set positions ====================
    // background
    reg.get_components<Component::Position>().insert_at(
        background,
        Component::Position(
            float(rendering::system::SCREEN_WIDTH) / 2,
            float(rendering::system::SCREEN_HEIGHT) / 2, -10
        )
    );
    // midground
    reg.get_components<Component::Position>().insert_at(
        midground,
        Component::Position(
            float(rendering::system::SCREEN_WIDTH) / 2,
            float(rendering::system::SCREEN_HEIGHT) / 2, -9
        )
    );
    // foreground
    reg.get_components<Component::Position>().insert_at(
        foreground,
        Component::Position(
            float(rendering::system::SCREEN_WIDTH) / 2,
            float(rendering::system::SCREEN_HEIGHT) / 2, -8
        )
    );
    // topBorder
    reg.get_components<Component::Position>().insert_at(
        topBorder, Component::Position(0, 0, -7)
    );
    // bottomBorder
    reg.get_components<Component::Position>().insert_at(
        bottomBorder,
        Component::Position(
            float(rendering::system::SCREEN_WIDTH) / 2,
            float(rendering::system::SCREEN_HEIGHT) - float(BORDERS_H) / 2, -7
        )
    );

    // ==================== set Drawable ====================
    // background
    reg.get_components<Component::Drawable>().insert_at(
        background, Component::Drawable(0, 512.0f, 192.0f, 2.0f)
    );
    // midground
    reg.get_components<Component::Drawable>().insert_at(
        midground, Component::Drawable(1, 512.0f, 192.0f, 2.0f)
    );
    // foreground
    reg.get_components<Component::Drawable>().insert_at(
        foreground, Component::Drawable(2, 512.0f, 192.0f, 2.0f)
    );
    // topBorder
    reg.get_components<Component::Drawable>().insert_at(
        topBorder, Component::Drawable(TOP_BORDER_I, BORDERS_W, BORDERS_H, 3)
    );
    // bottomBorder
    reg.get_components<Component::Drawable>().insert_at(
        bottomBorder, Component::Drawable(BOT_BORDER_I, BORDERS_W, BORDERS_H, 3)
    );

    // ==================== set Animation ====================
    reg.get_components<Component::Animation>().insert_at(
        background, Component::Animation(1024, 192, 512, 192, 1, 2)
    );
    reg.get_components<Component::Animation>().insert_at(
        midground, Component::Animation(1024, 192, 512, 192, 3, 2)
    );
    reg.get_components<Component::Animation>().insert_at(
        foreground, Component::Animation(1408, 192, 704, 192, 5, 1)
    );
    reg.get_components<Component::Animation>().insert_at(
        topBorder,
        Component::Animation(
            BORDERS_F * BORDERS_W, BORDERS_H, BORDERS_W, BORDERS_H, 1, 1
        )
    );
    reg.get_components<Component::Animation>().insert_at(
        bottomBorder,
        Component::Animation(
            BORDERS_F * BORDERS_W, BORDERS_H, BORDERS_W, BORDERS_H, 1, 1
        )
    );

    // ==================== set Collision ====================
    reg.get_components<Component::Collision>().insert_at(
        topBorder, Component::Collision(BORDERS_W, BORDERS_H * 3)
    );
    reg.get_components<Component::Collision>().insert_at(
        bottomBorder, Component::Collision(BORDERS_W, BORDERS_H * 3)
    );
    reg.get_components<Component::HitBox>().insert_at(
        topBorder, Component::HitBox(BORDERS_W * 3, BORDERS_H * 3)
    );
    reg.get_components<Component::HitBox>().insert_at(
        bottomBorder, Component::HitBox(BORDERS_W * 3, BORDERS_H * 3)
    );

    // ==================== set LifeTime ====================
    // register you're LifeTime components

    // ==================== set health ========================

    // ==================== set lifes ========================

    // ==================== set Text ====================

    reg.get_components<Component::Solid>().insert_at(
        topBorder, Component::Solid()
    );
    reg.get_components<Component::Solid>().insert_at(
        bottomBorder, Component::Solid()
    );
    // ==================== PLAYER ====================
    for (auto &client : this->_serverClients) {
        engine::Entity player(reg.get_new_entity());
        reg.get_components<Component::Position>().insert_at(
            player,
            Component::Position(
                150,
                int(rendering::system::SCREEN_HEIGHT / 2)
                    + (75.0 * (client.getPlayerNumber() - 2.5)),
                1
            )
        );
        reg.get_components<Component::Solid>().insert_at(
            player, Component::Solid()
        );
        reg.get_components<Component::Velocity>().insert_at(
            player, Component::Velocity()
        );
        reg.get_components<Component::Drawable>().insert_at(
            player,
            Component::Drawable(
                SHIP_I, SHIP_W, SHIP_H, 3, 17 * (client.getPlayerNumber() - 1)
            )
        );
        reg.get_components<Component::Animation>().insert_at(
            player,
            Component::Animation(
                SHIP_W * SHIP_F, SHIP_H, SHIP_W, SHIP_H, SHIP_W, 50
            )
        );
        reg.get_components<Component::Collision>().insert_at(
            player, Component::Collision(SHIP_W * 2, SHIP_H * 2)
        );
        reg.get_components<Component::HitBox>().insert_at(
            player, Component::HitBox(SHIP_W * 2, SHIP_H * 2)
        );
        reg.get_components<Component::FireRate>().insert_at(
            player, Component::FireRate(50)
        );
        reg.get_components<Component::Controllable>().insert_at(
            player, client.getPlayerNumber()
        );
        reg.get_components<Component::Health>().insert_at(
            player, Component::Health(2, 2)
        );
        reg.get_components<Component::Life>().insert_at(
            player, Component::Life(1)
        );

        engine::Entity name(reg.get_new_entity());
        reg.get_components<Component::Position>().insert_at(
            name, Component::Position()
        );
        std::string playerName = client.getPlayerName();
        reg.get_components<Component::Text>().insert_at(
            name,
            Component::Text(
                std::move(playerName), "./assets/fonts/Over_There.ttf", 15, 5,
                0xFFFFFFFF
            )
        );
        reg.get_components<Component::Velocity>().insert_at(
            name, Component::Velocity()
        );
        reg.get_components<Component::Follow>().insert_at(
            name, Component::Follow(player, 0, 50)
        );
    }
}

std::unique_ptr<engine::IGame> RTypeGame::createLobby()
{
    return std::make_unique<RTypeLobby>(*this);
}

engine::IGame *createGame()
{
    return new RTypeGame();
}
