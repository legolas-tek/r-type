/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** SpawnEnemySystem
*/

#include "SpawnEnemySystem.hpp"

#include <random>

#include "Rendering.hpp"

System::SpawnEnemySystem::SpawnEnemySystem(
    engine::Registry &reg, EntityInfo entityInfo, size_t startTick, size_t cycle
)
    : _register(reg)
    , _entityInfo(entityInfo)
    , _startTick(startTick)
    , _cycle(cycle)
{
    // EntityInfo mutalisk = { 5, 320, 72, 64, 72, 64, 10, 0, 0, 2.0f };
    // EntityInfo scourge = { 6, 155, 27, 31, 27, 31, 10, 0, 0, 2.0f };

    // _entityList.push_back(mutalisk);
    // _entityList.push_back(scourge);
}

// static void addEntity(engine::Registry &reg, EntityInfo entityInfo)
// {
//     engine::Entity enemy(reg.get_new_entity());
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     int possiblePosY = static_cast<int>(
//         rendering::system::SCREEN_HEIGHT - entityInfo.entityHeight
//     );
//     std::uniform_int_distribution<> distrib(0, possiblePosY);

//     int randomY = distrib(gen);

//     // set position
//     reg.get_components<Component::Position>().insert_at(
//         enemy, std::move(Component::Position(700, randomY, 0))
//     );
//     // set Drawable
//     reg.get_components<Component::Drawable>().insert_at(
//         enemy,
//         std::move(Component::Drawable(
//             entityInfo.textureIndex, entityInfo.entityWidth,
//             entityInfo.entityHeight, entityInfo.scale
//         ))
//     );
//     // set Animation
//     reg.get_components<Component::Animation>().insert_at(
//         enemy,
//         std::move(Component::Animation(
//             entityInfo.textureWidth, entityInfo.textureHeight,
//             entityInfo.entityWidth, entityInfo.entityHeight,
//             entityInfo.offset, entityInfo.frameDuration
//         ))
//     );
// }

// void System::SpawnEnemySystem::addEnemy()
// {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> distrib(0, 1);
//     int randomValue = distrib(gen);

//     addEntity(_register, _entityList[randomValue]);
// }

void System::SpawnEnemySystem::operator()()
{
    if ((_register.getTick() - _startTick) % _cycle != 0) {
        return;
    }

    engine::Entity enemy(_register.get_new_entity());
    std::random_device rd;
    std::mt19937 gen(rd());
    int possiblePosY = static_cast<int>(
        rendering::system::SCREEN_HEIGHT - _entityInfo.entityHeight
    );
    std::uniform_int_distribution<> distrib(0, possiblePosY);

    int randomY = distrib(gen);

    // set position
    _register.get_components<Component::Position>().insert_at(
        enemy, std::move(Component::Position(700, randomY, 0))
    );
    // set Drawable
    _register.get_components<Component::Drawable>().insert_at(
        enemy,
        std::move(Component::Drawable(
            _entityInfo.textureIndex, _entityInfo.entityWidth,
            _entityInfo.entityHeight, _entityInfo.scale
        ))
    );
    // set Animation
    _register.get_components<Component::Animation>().insert_at(
        enemy,
        std::move(Component::Animation(
            _entityInfo.textureWidth, _entityInfo.textureHeight,
            _entityInfo.entityWidth, _entityInfo.entityHeight,
            _entityInfo.offset, _entityInfo.frameDuration
        ))
    );
}
