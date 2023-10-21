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
#include "Components/HitBox.hpp"
#include "Components/Health.hpp"
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
    _register.get_components<Component::Position>().insert_at(
        enemy, Component::Position(randomX, randomY, 0)
    );
    // set Drawable
    _register.get_components<Component::Drawable>().insert_at(
        enemy,
        Component::Drawable(
            _entityInfo.textureIndex, _entityInfo.entityWidth,
            _entityInfo.entityHeight, _entityInfo.scale
        )
    );
    // set Animation
    _register.get_components<Component::Animation>().insert_at(
        enemy,
        Component::Animation(
            _entityInfo.textureWidth, _entityInfo.textureHeight,
            _entityInfo.entityWidth, _entityInfo.entityHeight,
            _entityInfo.offset, _entityInfo.frameDuration
        )
    );
    _register.get_components<Component::LifeTime>().insert_at(
        enemy, Component::LifeTime(200, _register.getTick())
    );
    _register.get_components<Component::Velocity>().insert_at(
        enemy, Component::Velocity(-5, 0)
    );
    _register.get_components<Component::HitBox>().insert_at(
        enemy,
        Component::HitBox(
            _entityInfo.entityWidth * _entityInfo.scale,
            _entityInfo.entityHeight * _entityInfo.scale
        )
    );
    _register.get_components<Component::Collision>().insert_at(
        enemy,
        Component::Collision(
            _entityInfo.entityWidth * _entityInfo.scale,
            _entityInfo.entityHeight * _entityInfo.scale
        )
    );
    _register.get_components<Component::Damage>().insert_at(
        enemy, Component::Damage(1)
    );
    _register.get_components<Component::Health>().insert_at(
        enemy, Component::Health(1)
    );
}
