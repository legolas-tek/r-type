/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** MarioGame
*/

#include "MarioGame.hpp"

#include "Components/Animation.hpp"
#include "Components/Controllable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "Components/Solid.hpp"
#include "Components/Text.hpp"
#include "Components/Velocity.hpp"

#include "Systems/CollisionsSystem.hpp"
#include "Systems/MoveSystem.hpp"

#include "Key.hpp"
#include "Rendering.hpp"

#include <iostream>

void MarioGame::registerAllComponents(engine::Registry &reg)
{
    // to use system rendering -> texture
    reg.register_component<Component::Drawable>();
    reg.register_component<Component::Animation>();
    // to use system rendering -> text
    reg.register_component<Component::Text>();
    // to use system rendering -> texture & text
    reg.register_component<Component::Position>();

    // collisionn
    reg.register_component<Component::HitBox>();
    reg.register_component<Component::Collision>();
    reg.register_component<Component::Solid>();
    // physics
    reg.register_component<Component::Velocity>();
    reg.register_component<Component::Controllable>();
}

void MarioGame::registerAdditionalServerSystems(engine::Registry &reg)
{
}

void MarioGame::registerAdditionalClientSystems(engine::Registry &reg)
{
    reg.add_system<System::CollisionsSystem>(
        reg.events, reg.get_components<Component::Position>(),
        reg.get_components<Component::HitBox>(),
        reg.get_components<Component::Collision>()
    );
    reg.add_system<rendering::system::Rendering>(reg);
    reg.add_system<System::MoveSystem>(
        reg.events, reg.get_components<Component::Position>(),
        reg.get_components<Component::Velocity>(),
        reg.get_components<Component::Solid>(),
        reg.get_components<Component::Collision>()
    );
    reg.add_system<rendering::system::Key>(
        reg.get_components<Component::Controllable>(),
        reg.get_components<Component::Velocity>(), 0
    );
}

void MarioGame::registerAdditionalSystems(engine::Registry &reg)
{
}

void MarioGame::initAssets(engine::Registry &reg)
{
    reg._assets_paths.emplace_back("./assets/mario/images/mario_floor.png");
    reg._assets_paths.emplace_back("./assets/mario/images/mario_background.png"
    );
    reg._assets_paths.emplace_back("./assets/mario/images/mario.png");
}

void MarioGame::initScene(engine::Registry &reg)
{
    engine::Entity floor(reg.get_new_entity());
    engine::Entity background(reg.get_new_entity());
    engine::Entity mario_player(reg.get_new_entity());

    // one box is 16 * 16
    float oneUnit = ONE_UNIT;

    float scaleRatio = static_cast<float>(rendering::system::SCREEN_HEIGHT)
        / WIDNOW_SPRITE_HEIGHT;

    float marioScale = oneUnit / MARIO_ONE_SPRITE_HEIGHT * scaleRatio;

    // ==================== set Drawable ====================
    // floor
    reg.get_components<Component::Drawable>().insert_at(
        floor,
        Component::Drawable(
            0, WIDNOW_SPRITE_WIDTH, FLOOR_SPRITE_HEIGHT, scaleRatio
        )
    );
    // background
    reg.get_components<Component::Drawable>().insert_at(
        background,
        Component::Drawable(
            1, WIDNOW_SPRITE_WIDTH, BACKGROUND_SPRITE_HEIGHT, scaleRatio
        )
    );
    // mario_player
    reg.get_components<Component::Drawable>().insert_at(
        mario_player,
        Component::Drawable(
            2, MARIO_ONE_SPRITE_WIDTH, MARIO_ONE_SPRITE_HEIGHT, marioScale
        )
    );
    // ==================== set positions ====================
    // floor
    reg.get_components<Component::Position>().insert_at(
        floor,
        Component::Position(
            0.0,
            float(rendering::system::SCREEN_HEIGHT)
                - (FLOOR_SPRITE_HEIGHT * scaleRatio),
            0
        )
    );
    // background
    reg.get_components<Component::Position>().insert_at(
        background, Component::Position(0.0, 0.0f, 0)
    );
    // mario_player
    reg.get_components<Component::Position>().insert_at(
        mario_player,
        Component::Position(
            0.0,
            float(rendering::system::SCREEN_HEIGHT)
                - (FLOOR_SPRITE_HEIGHT * scaleRatio) - (oneUnit * scaleRatio)
                - 10,
            0
        )
    );
    // ==================== set Collision ====================
    reg.get_components<Component::HitBox>().insert_at(
        mario_player,
        Component::HitBox(
            MARIO_ONE_SPRITE_WIDTH * marioScale,
            MARIO_ONE_SPRITE_HEIGHT * marioScale
        )
    );
    // ==================== set Collision ====================
    reg.get_components<Component::Collision>().insert_at(
        floor,
        Component::Collision(
            WIDNOW_SPRITE_WIDTH * scaleRatio, FLOOR_SPRITE_HEIGHT * scaleRatio
        )
    );
    // ==================== set Collision ====================
    reg.get_components<Component::Solid>().insert_at(floor, Component::Solid());
    // ==================== set Velocity ====================
    reg.get_components<Component::Velocity>().insert_at(
        mario_player, Component::Velocity(1, 1)
    );
    // ==================== set Controllable ====================
    reg.get_components<Component::Controllable>().insert_at(mario_player, 0);
}

engine::IGame *createGame()
{
    return new MarioGame();
}
