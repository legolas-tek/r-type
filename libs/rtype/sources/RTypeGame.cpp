/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game
*/

#include "Components/ScoreOnDeath.hpp"
#include "Game.hpp"

#include "Components/Bonus.hpp"
#include "Components/ChatModifiableText.hpp"
#include "Components/Focusable.hpp"
#include "Components/RestartOnClick.hpp"
#include "Components/Solid.hpp"
#include "Components/Text.hpp"

#include "Systems/AnimationSystem.hpp"
#include "Systems/AttackSystem.hpp"
#include "Systems/CollisionsSystem.hpp"
#include "Systems/DamageHandler.hpp"
#include "Systems/DamageOnCollisionSystem.hpp"
#include "Systems/DeathAnimationManager.hpp"
#include "Systems/DeathOnCollisions.hpp"
#include "Systems/DeathSystem.hpp"
#include "Systems/End.hpp"
#include "Systems/EndGameSystem.hpp"
#include "Systems/FloatingSystem.hpp"
#include "Systems/Focusable.hpp"
#include "Systems/FollowSystem.hpp"
#include "Systems/LifeTimeSystem.hpp"
#include "Systems/LootDropManager.hpp"
#include "Systems/MoveSystem.hpp"
#include "Systems/NetworkSystem.hpp"
#include "Systems/ProcessKeyDownEvents.hpp"
#include "Systems/ProcessKeyPressedEvents.hpp"
#include "Systems/RespawnSystem.hpp"
#include "Systems/Restart.hpp"
#include "Systems/ScoreOnDeath.hpp"
#include "Systems/SoundManagerSystem.hpp"
#include "Systems/SpawnEnemySystem.hpp"
#include "Systems/TriggerBonus.hpp"
#include "Systems/WaveManagerSystem.hpp"

#include "Key.hpp"
#include "Rendering.hpp"

#ifdef DEBUG_LOG_DIFF
    #include "DiffLogger.hpp"
#endif
#ifdef DEBUG_LOG_EVENT
    #include "Systems/EventLogger.hpp"
#endif

void RTypeGame::registerAllComponents(engine::Registry &reg)
{
    reg.register_component<Component::Position>();
    reg.register_component<Component::Velocity>();
    reg.register_component<Component::ChatModifiableText>();
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
    reg.register_component<Component::Dependent>();
    reg.register_component<Component::RestartOnClick>();
    reg.register_component<Component::Focusable>();
    reg.register_component<Component::KillOnCollision>();
    reg.register_component<Component::Loot>();
    reg.register_component<Component::Bonus>();
    reg.register_component<Component::ScoreOnDeath>();
}

void RTypeGame::registerAdditionalServerSystems(engine::Registry &reg)
{
    reg.add_system<System::LootDropManager>(
        reg.get_components<Component::Loot>(),
        reg.get_components<Component::Position>(), reg, 10
    );
    reg.add_system<System::DeathOnCollisions>(
        reg.get_components<Component::Solid>(),
        reg.get_components<Component::KillOnCollision>(), reg.events
    );
    reg.add_system<System::DeathAnimationManager>(
        reg.get_components<Component::Position>(),
        reg.get_components<Component::Health>(), reg
    );
    reg.add_system<System::ScoreOnDeath>(
        reg.events, *_scoreManager,
        reg.get_components<Component::ScoreOnDeath>()
    );
    reg.add_system<System::DeathSystem>(
        reg.get_components<Component::Health>(),
        reg.get_components<Component::Life>(),
        reg.get_components<Component::Dependent>(),
        reg.get_components<Component::Follow>(), reg
    );
    reg.add_system<System::TriggerBonus>(
        reg.get_components<Component::Bonus>(),
        reg.get_components<Component::Controllable>(),
        reg.get_components<Component::Life>(), reg
    );
    reg.add_system<System::AttackSystem>(
        reg.get_components<Component::FireRate>(),
        reg.get_components<Component::Health>(),
        reg.get_components<Component::Position>(), reg
    );
    reg.add_system<System::LifeTimeSystem>(
        reg.get_components<Component::LifeTime>(), reg
    );
    reg.add_system<System::DamageOnCollisionSystem>(
        reg.get_components<Component::Damage>(),
        reg.get_components<Component::Health>(), reg.events
    );
    reg.add_system<System::DamageHandler>(
        reg.get_components<Component::Health>(), reg.events
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
    reg.add_system<System::WaveManagerSystem>(reg);
    reg.add_system<System::FloatingSystem>(
        reg.get_components<Component::Position>(),
        reg.get_components<Component::Velocity>(),
        reg.get_components<Component::Floating>()
    );
    reg.add_system<System::End>(
        reg.events, reg.get_components<Component::Controllable>()
    );
    reg.add_system<System::EndGameSystem>(reg.events, reg, *_scoreManager);
    reg.add_system<rtype::NetworkServerSystem>(reg, 4242, _serverClients);
}

void RTypeGame::registerAdditionalClientSystems(engine::Registry &reg)
{
    reg.add_system<rendering::system::Focusable>(
        reg.events, reg.get_components<Component::Focusable>(),
        reg.get_components<Component::HitBox>(),
        reg.get_components<Component::Position>()
    );
    reg.add_system<System::SoundManagerSystem>(reg);
    reg.add_system<System::AnimationSystem>(reg);
    reg.add_system<rendering::system::Rendering>(reg);
    reg.add_system<rendering::system::Key>(reg.events);

    reg.add_system<System::ProcessKeyDownEvents>(
        reg.events, reg.get_components<Component::Controllable>(),
        reg.get_components<Component::Velocity>(), _playerNumber
    );

    reg.add_system<System::ProcessKeyPressedEvents>(
        reg.events, _playerNumber, reg.getTick(),
        reg.get_components<Component::Text>(),
        reg.get_components<Component::ChatModifiableText>()
    );

    reg.add_system<System::Restart>(
        reg.events, reg.get_components<Component::RestartOnClick>(),
        reg.get_components<Component::Focusable>()
    );
    reg.add_system<rtype::NetworkClientSystem>(
        reg, _address, _port, _playerNumber, _playerHash
    );
}

void RTypeGame::registerAdditionalSystems(engine::Registry &reg)
{
#ifdef DEBUG_LOG_DIFF
    reg.add_system<net::system::DiffLogger>(reg);
#endif
    reg.add_system<System::CollisionsSystem>(
        reg.events, reg.get_components<Component::Position>(),
        reg.get_components<Component::HitBox>(),
        reg.get_components<Component::Collision>()
    );
    reg.add_system<System::MoveSystem>(
        reg.events, reg.get_components<Component::Position>(),
        reg.get_components<Component::Velocity>(),
        reg.get_components<Component::Solid>(),
        reg.get_components<Component::Collision>()
    );
    reg.add_system<System::FollowSystem>(
        reg.get_components<Component::Follow>(),
        reg.get_components<Component::Position>()
    );
#ifdef DEBUG_LOG_EVENT
    reg.add_system<System::EventLogger>("rtype", reg.tick(), reg.events);
#endif
}

void RTypeGame::initAssets(engine::Registry &reg)
{
    // 0
    reg._assets_paths.emplace_back(
        "./assets/images/cyberpunk_street_background.png"
    );
    // 1
    reg._assets_paths.emplace_back(
        "./assets/images/cyberpunk_street_midground.png"
    );
    // 2
    reg._assets_paths.emplace_back(
        "./assets/images/cyberpunk_street_foreground.png"
    );
    // 3
    reg._assets_paths.emplace_back("./assets/images/space_ships.png");
    // 4
    reg._assets_paths.emplace_back("./assets/images/Plasma_Beam.png");
    // 5
    reg._assets_paths.emplace_back("./assets/images/impact_explosion.png");
    // 6
    reg._assets_paths.emplace_back("./assets/images/basic_ennemy.png");
    // 7
    reg._assets_paths.emplace_back("./assets/images/shooting_ennemy.png");
    // 8
    reg._assets_paths.emplace_back(
        "./assets/images/first_level_bottom_borders.png"
    );
    // 9
    reg._assets_paths.emplace_back("./assets/images/first_level_top_borders.png"
    );
    // 10
    reg._assets_paths.emplace_back("./assets/images/big_explosion.png");
    // 11
    reg._assets_paths.emplace_back("./assets/images/small_turret.png");
    // 12
    reg._assets_paths.emplace_back("./assets/images/first_boss.png");
    // 13
    reg._assets_paths.emplace_back("./assets/images/Spinning-orb.png");
    // 14
    reg._assets_paths.emplace_back("./assets/images/wrench.png");
}

void RTypeGame::initScene(engine::Registry &reg)
{
    engine::Entity background(reg.get_new_entity());
    engine::Entity midground(reg.get_new_entity());
    engine::Entity foreground(reg.get_new_entity());
    engine::Entity topBorder(reg.get_new_entity());
    engine::Entity bottomBorder(reg.get_new_entity());
    engine::Entity scoreText(reg.get_new_entity());

    // ==================== set positions ====================
    // background
    reg.get_components<Component::Position>().emplace_at(
        background, float(rendering::system::SCREEN_WIDTH) / 2,
        float(rendering::system::SCREEN_HEIGHT) / 2, -9999
    );
    // midground
    reg.get_components<Component::Position>().emplace_at(
        midground, float(rendering::system::SCREEN_WIDTH) / 2,
        float(rendering::system::SCREEN_HEIGHT) / 2, -9998
    );
    // foreground
    reg.get_components<Component::Position>().emplace_at(
        foreground, float(rendering::system::SCREEN_WIDTH) / 2,
        float(rendering::system::SCREEN_HEIGHT) / 2, -9997
    );
    // topBorder
    reg.get_components<Component::Position>().emplace_at(topBorder, 0, 0, -7);
    // bottomBorder
    reg.get_components<Component::Position>().emplace_at(
        bottomBorder, float(rendering::system::SCREEN_WIDTH) / 2,
        float(rendering::system::SCREEN_HEIGHT) - float(BORDERS_H) / 2, -7
    );
    // scoreText
    reg.get_components<Component::Position>().emplace_at(
        scoreText, 150, 25, -5
    );

    // ==================== set Drawable ====================
    // background
    reg.get_components<Component::Drawable>().emplace_at(
        background, 0, 512.0f, 192.0f, 3.8f
    );
    // midground
    reg.get_components<Component::Drawable>().emplace_at(
        midground, 1, 512.0f, 192.0f, 3.8f
    );
    // foreground
    reg.get_components<Component::Drawable>().emplace_at(
        foreground, 2, 512.0f, 192.0f, 3.8f
    );
    // topBorder
    reg.get_components<Component::Drawable>().emplace_at(
        topBorder, TOP_BORDER_I, BORDERS_W, BORDERS_H, 3
    );
    // bottomBorder
    reg.get_components<Component::Drawable>().emplace_at(
        bottomBorder, BOT_BORDER_I, BORDERS_W, BORDERS_H, 3
    );

    // ==================== set Animation ====================
    reg.get_components<Component::Animation>().insert_at(
        background, Component::Animation(1024, 192, 512, 192, 1, 2)
    );
    reg.get_components<Component::Animation>().insert_at(
        midground, Component::Animation(1024, 192, 512, 192, 3, 2)
    );
    reg.get_components<Component::Animation>().emplace_at(
        foreground, 1408, 192, 704, 192, 5, 1
    );
    reg.get_components<Component::Animation>().emplace_at(
        topBorder, BORDERS_F * BORDERS_W, BORDERS_H, BORDERS_W, BORDERS_H, 1, 1
    );
    reg.get_components<Component::Animation>().emplace_at(
        bottomBorder, BORDERS_F * BORDERS_W, BORDERS_H, BORDERS_W, BORDERS_H, 1,
        1
    );

    // ==================== set Collision ====================
    reg.get_components<Component::Collision>().emplace_at(
        topBorder, BORDERS_W * 3, BORDERS_H * 3
    );
    reg.get_components<Component::Collision>().emplace_at(
        bottomBorder, BORDERS_W * 3, BORDERS_H * 3
    );
    reg.get_components<Component::HitBox>().emplace_at(
        topBorder, BORDERS_W * 3, BORDERS_H * 3
    );
    reg.get_components<Component::HitBox>().emplace_at(
        bottomBorder, BORDERS_W * 3, BORDERS_H * 3
    );

    // ==================== set LifeTime ====================
    // register you're LifeTime components

    // ==================== set health ========================

    // ==================== set lifes ========================

    // ==================== set Text ====================
    _scoreManager.emplace(*reg.get_components<Component::Text>().emplace_at(
        scoreText, "Score", "./assets/fonts/Over_There.ttf", 20, 10, 0xFFFFFFFF
    ));

    reg.get_components<Component::Solid>().emplace_at(topBorder);
    reg.get_components<Component::Solid>().emplace_at(bottomBorder);
    // ==================== PLAYER ====================
    for (auto &client : this->_serverClients) {
        if (client.getPlayerNumber() == 0)
            continue; // spectator
        engine::Entity player(reg.get_new_entity());
        reg.get_components<Component::Position>().emplace_at(
            player,
            // 10.0f, 10.0f, 0.0f
            150,
            int(rendering::system::SCREEN_HEIGHT / 2)
                + (75.0 * (client.getPlayerNumber() - 2.5)),
            0
        );
        reg.get_components<Component::Solid>().emplace_at(player);
        reg.get_components<Component::Velocity>().emplace_at(player);
        reg.get_components<Component::Drawable>().emplace_at(
            player, SHIP_I, SHIP_W, SHIP_H, 3,
            17 * (client.getPlayerNumber() - 1)
        );
        reg.get_components<Component::Animation>().emplace_at(
            player, SHIP_W * SHIP_F, SHIP_H, SHIP_W, SHIP_H, SHIP_W, 50
        );
        reg.get_components<Component::Collision>().emplace_at(
            player, SHIP_W * 2, SHIP_H * 2
        );
        reg.get_components<Component::HitBox>().emplace_at(
            player, SHIP_W * 2, SHIP_H * 2
        );
        reg.get_components<Component::FireRate>().emplace_at(
            player, SHIP_FIRE_RATE
        );
        reg.get_components<Component::Controllable>().emplace_at(
            player, client.getPlayerNumber()
        );
        reg.get_components<Component::Health>().emplace_at(player, 2, 2);
        reg.get_components<Component::Life>().emplace_at(player, 3);

        engine::Entity reaction(reg.get_new_entity());
        reg.get_components<Component::Position>().emplace_at(reaction);
        reg.get_components<Component::Text>().emplace_at(
            reaction, "", "./assets/fonts/Over_There.ttf", 15, 5, 0xFFFFFFFF
        );
        reg.get_components<Component::Follow>().emplace_at(
            reaction, player, 0, -50
        );
        reg.get_components<Component::ChatModifiableText>().emplace_at(
            reaction, client.getPlayerNumber()
        );

        engine::Entity name(reg.get_new_entity());
        reg.get_components<Component::Position>().emplace_at(name);
        std::string playerName = client.getPlayerName();
        reg.get_components<Component::Text>().emplace_at(
            name, std::move(playerName), "./assets/fonts/Over_There.ttf", 15, 5,
            0xFFFFFFFF
        );
        reg.get_components<Component::Velocity>().emplace_at(name);
        reg.get_components<Component::Follow>().emplace_at(name, player, 0, 50);
        reg.get_components<Component::Damage>().emplace_at(player, 2);
    }
}
