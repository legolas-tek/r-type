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
    std::cout << "Mario registerAllComponents" << std::endl;
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
    std::cout << "Mario registerAdditionalServerSystems" << std::endl;
}

void MarioGame::registerAdditionalClientSystems(engine::Registry &reg)
{
    std::cout << "Mario registerAdditionalClientSystems" << std::endl;
    reg.add_system<rendering::system::Rendering>(reg);
}

void MarioGame::registerAdditionalSystems(engine::Registry &reg)
{
    std::cout << "Mario registerAdditionalSystems" << std::endl;
}

void MarioGame::initAssets(engine::Registry &reg)
{
    std::cout << "Mario initAssets" << std::endl;
}

void MarioGame::initScene(engine::Registry &reg)
{
    std::cout << "Mario initScene" << std::endl;
}

engine::IGame *createGame()
{
    return new MarioGame();
}
