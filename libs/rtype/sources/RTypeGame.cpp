/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game
*/

#include "Game.hpp"

#include "Components/Text.hpp"

#include "Systems/AnimationSystem.hpp"
#include "Systems/AttackSystem.hpp"
#include "Systems/CollisionsSystem.hpp"
#include "Systems/DamageSystem.hpp"
#include "Systems/DeathAnimationManager.hpp"
#include "Systems/DeathSystem.hpp"
#include "Systems/LifeTimeSystem.hpp"
#include "Systems/MoveSystem.hpp"
#include "Systems/NetworkSystem.hpp"
#include "Systems/SoundManagerSystem.hpp"
#include "Systems/SpawnEnemySystem.hpp"
#include "Systems/WaveManagerSystem.hpp"

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
    reg.register_component<Component::Life>();
    reg.register_component<Component::Text>();
}

void RTypeGame::registerAdditionalServerSystems(engine::Registry &reg)
{
    reg.add_system<System::WaveManagerSystem>(reg);
    reg.add_system<System::CollisionsSystem>(
        reg.get_components<Component::Position>(),
        reg.get_components<Component::HitBox>(),
        reg.get_components<Component::Collision>()
    );
    reg.add_system<System::AttackSystem>(
        reg.get_components<Component::FireRate>(), reg
    );
    reg.add_system<System::LifeTimeSystem>(
        reg.get_components<Component::LifeTime>(), reg
    );
    reg.add_system<System::DamageSystem>(
        reg.get_components<Component::Damage>(),
        reg.get_components<Component::Life>(),
        reg.get_components<Component::Collision>(), reg
    );
    reg.add_system<System::DeathAnimationManager>(
        reg.get_components<Component::Life>(),
        reg.get_components<Component::Collision>(),
        reg.get_components<Component::Damage>(), reg
    );
    reg.add_system<System::DeathSystem>(
        reg.get_components<Component::Life>(), reg
    );
    reg.add_system<rtype::NetworkServerSystem>(reg, 4242);
}

void RTypeGame::registerAdditionalClientSystems(engine::Registry &reg)
{
    reg.add_system<System::AnimationSystem>(reg);
    reg.add_system<System::SoundManagerSystem>(reg);
    reg.add_system<System::WaveManagerSystem>(reg);
    reg.add_system<rendering::system::Rendering>(reg);
    reg.add_system<rendering::system::Key>(reg);
    reg.add_system<net::system::NetworkClient>(reg, 4242);
}

void RTypeGame::registerAdditionalSystems(engine::Registry &reg)
{
    reg.add_system<System::MoveSystem>(
        reg.get_components<Component::Position>(),
        reg.get_components<Component::Velocity>()
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
}

void RTypeGame::initScene(engine::Registry &reg)
{
    engine::Entity background(reg.get_new_entity());
    engine::Entity midground(reg.get_new_entity());
    engine::Entity foreground(reg.get_new_entity());
    engine::Entity player(reg.get_new_entity());
    engine::Entity topBorder(reg.get_new_entity());
    engine::Entity bottomBorder(reg.get_new_entity());

    // ==================== set positions ====================
    // background
    reg.get_components<Component::Position>().insert_at(
        background, Component::Position(0, 0, 0)
    );
    // midground
    reg.get_components<Component::Position>().insert_at(
        midground, Component::Position(0, 0, 0)
    );
    // foreground
    reg.get_components<Component::Position>().insert_at(
        foreground, Component::Position(0, 0, 0)
    );
    // player
    reg.get_components<Component::Position>().insert_at(
        player, Component::Position(150, 150, 1)
    );
    // topBorder
    reg.get_components<Component::Position>().insert_at(
        topBorder, Component::Position(0, 0, 1)
    );
    // bottomBorder
    reg.get_components<Component::Position>().insert_at(
        bottomBorder,
        Component::Position(0, rendering::system::SCREEN_HEIGHT - 16, 1)
    );

    // ==================== set velocity ====================
    reg.get_components<Component::Velocity>().insert_at(
        player, Component::Velocity()
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
    // player
    reg.get_components<Component::Drawable>().insert_at(
        player, Component::Drawable(SHIP_I, SHIP_W, SHIP_H, 3)
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
        background, Component::Animation(1024, 192, 512, 192, 1, 1)
    );
    reg.get_components<Component::Animation>().insert_at(
        midground, Component::Animation(1024, 192, 512, 192, 3, 1)
    );
    reg.get_components<Component::Animation>().insert_at(
        foreground, Component::Animation(1408, 192, 704, 192, 5, 1)
    );
    reg.get_components<Component::Animation>().insert_at(
        player,
        Component::Animation(
            SHIP_W * SHIP_F, SHIP_H, SHIP_W, SHIP_H, SHIP_W, 50
        )
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

    // // ==================== set Controllable ====================
    reg.get_components<Component::Controllable>().insert_at(player, 2);

    // ==================== set Collision ====================
    reg.get_components<Component::Collision>().insert_at(
        player, Component::Collision(SHIP_W, SHIP_H)
    );

    // ==================== set Hitbox ====================
    reg.get_components<Component::HitBox>().insert_at(
        player, Component::HitBox(SHIP_W, SHIP_H)
    );

    // ==================== set FireRate ====================
    reg.get_components<Component::FireRate>().insert_at(
        player, Component::FireRate(50)
    );

    // ==================== set LifeTime ====================
    // register you're LifeTime components

    // ==================== set Life ========================
    reg.get_components<Component::Life>().insert_at(player, Component::Life(3));

    // ==================== set Text ====================
}

std::unique_ptr<engine::IGame> RTypeGame::createLobby()
{
    // TODO: fix the lobby before changing this line
    // return std::make_unique<RTypeLobby>();
    return nullptr;
}

engine::IGame *createGame()
{
    return new RTypeGame();
}
