/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** MarioGame
*/

#include "MarioGame.hpp"

#include "Components/Animation.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "Components/Text.hpp"

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
}

void MarioGame::registerAdditionalServerSystems(engine::Registry &reg)
{
}

void MarioGame::registerAdditionalClientSystems(engine::Registry &reg)
{
    reg.add_system<rendering::system::Rendering>(reg);
}

void MarioGame::registerAdditionalSystems(engine::Registry &reg)
{
}

void MarioGame::initAssets(engine::Registry &reg)
{
    reg._assets_paths.emplace_back("./assets/mario/images/mario_floor.png");
    reg._assets_paths.emplace_back("./assets/mario/images/mario_background.png"
    );
}

void MarioGame::initScene(engine::Registry &reg)
{
    engine::Entity floor(reg.get_new_entity());
    engine::Entity background(reg.get_new_entity());

    float scaleRatio
        = static_cast<float>(rendering::system::SCREEN_HEIGHT) / 224.0;

    // ==================== set Drawable ====================
    // floor
    reg.get_components<Component::Drawable>().insert_at(
        floor, Component::Drawable(0, 1564.0f, 24.0f, scaleRatio)
    );
    std::cout << "test " << scaleRatio << std::endl;
    // background
    reg.get_components<Component::Drawable>().insert_at(
        background, Component::Drawable(1, 1564.0f, 200.0f, scaleRatio)
    );

    // ==================== set positions ====================
    // floor
    reg.get_components<Component::Position>().insert_at(
        floor,
        Component::Position(
            0.0, float(rendering::system::SCREEN_HEIGHT) - (24.0 * scaleRatio),
            0
        )
    );
    // background
    reg.get_components<Component::Position>().insert_at(
        background, Component::Position(0.0, 0.0f, 0)
    );
}

engine::IGame *createGame()
{
    return new MarioGame();
}
