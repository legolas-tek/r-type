/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** SpawnEnemySystem
*/

#include "SpawnEnemySystem.hpp"
#include "Rendering.hpp"

#include "Components/Collision.hpp"
#include "Components/Damage.hpp"
#include "Components/Health.hpp"
#include "Components/HitBox.hpp"
#include "Components/LifeTime.hpp"
#include "Components/Velocity.hpp"

System::SpawnEnemySystem::SpawnEnemySystem(
    engine::Registry &reg, EntityInfo entityInfo, size_t startTick,
    size_t cycle, float minX, float maxX, float minY, float maxY
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
    std::uniform_real_distribution<float> distribX(_minX, _maxX);
    std::uniform_real_distribution<float> distribY(_minY, _maxY);

    auto randomX = distribX(_gen);
    auto randomY = distribY(_gen);

    // set position
    _register.get_components<Component::Position>().emplace_at(
        enemy, randomX, randomY, 0
    );
    // set Drawable
    _register.get_components<Component::Drawable>().emplace_at(
        enemy, _entityInfo.textureIndex, _entityInfo.entityWidth,
        _entityInfo.entityHeight, _entityInfo.scale
    );
    // set Animation
    _register.get_components<Component::Animation>().emplace_at(
        enemy, _entityInfo.textureWidth, _entityInfo.textureHeight,
        _entityInfo.entityWidth, _entityInfo.entityHeight, _entityInfo.offset,
        _entityInfo.frameDuration
    );
    _register.get_components<Component::LifeTime>().emplace_at(
        enemy, 200, _register.getTick()
    );
    _register.get_components<Component::Velocity>().emplace_at(
        enemy, -5, 0
    );
    _register.get_components<Component::HitBox>().emplace_at(
        enemy, _entityInfo.entityWidth * _entityInfo.scale,
        _entityInfo.entityHeight * _entityInfo.scale
    );
    _register.get_components<Component::Collision>().emplace_at(
        enemy, _entityInfo.entityWidth * _entityInfo.scale,
        _entityInfo.entityHeight * _entityInfo.scale
    );
    _register.get_components<Component::Damage>().emplace_at(
        enemy, 1
    );
    _register.get_components<Component::Health>().emplace_at(
        enemy, 1, 1
    );
}
