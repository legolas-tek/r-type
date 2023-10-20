/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** SpawnEnemySystem
*/

#include "SpawnEnemySystem.hpp"

#include "Rendering.hpp"

System::SpawnEnemySystem::SpawnEnemySystem(
    engine::Registry &reg, EntityInfo entityInfo, size_t startTick,
    size_t cycle, int minX, int maxX, int minY, int maxY
)
    : _register(reg)
    , _entityInfo(entityInfo)
    , _startTick(startTick)
    , _cycle(cycle)
    , _minX(minX)
    , _maxX(maxX)
    , _minY(minY)
    , _maxY(maxY)
    , _gen(rd())
{
}

void System::SpawnEnemySystem::operator()()
{
    if ((_register.getTick() - _startTick) % _cycle != 0) {
        return;
    }

    engine::Entity enemy(_register.get_new_entity());
    std::uniform_int_distribution<> distribX(_minX, _maxX);
    std::uniform_int_distribution<> distribY(_minY, _maxY);

    int randomX = distribX(_gen);
    int randomY = distribY(_gen);

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
