/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DamageSystem
*/

#include <iostream>

#include "Systems/DamageSystem.hpp"

#include "Components/Animation.hpp"
#include "Components/Drawable.hpp"
#include "Components/LifeTime.hpp"

System::DamageSystem::DamageSystem(
    SparseArray<Component::Damage> &damages,
    SparseArray<Component::Life> &lifes,
    SparseArray<Component::Collision> &collisions, engine::Registry &registry
)
    : _damages(damages)
    , _lifes(lifes)
    , _collisions(collisions)
    , _registry(registry)
{
}

void System::DamageSystem::operator()()
{
    for (auto it = _collisions.begin(); it != _collisions.end(); it++) {
        if ((*it)->_collidingEntity && isDamageCollision(it.get_entity())) {
            damageEntity(it.get_entity());
        }
    }
}

bool System::DamageSystem::isDamageCollision(engine::Entity const collidedEntity
)
{
    engine::Entity const collidingEntity
        = _collisions[collidedEntity]->_collidingEntity.value();

    return (_lifes[collidedEntity] && _damages[collidingEntity]);
}

void System::DamageSystem::damageEntity(engine::Entity const collidedEntity)
{
    engine::Entity const collidingEntity
        = _collisions[collidedEntity]->_collidingEntity.value();

    _lifes[collidedEntity]->life -= _damages[collidingEntity]->damages;
    createExplosion(
        _registry.get_components<Component::Position>()[collidingEntity].value()
    );
    _registry.erase_entity(collidingEntity);
    if (_lifes[collidedEntity]->life <= 0) {
        createBigExplosion(
            _registry.get_components<Component::Position>()[collidedEntity].value()
        );
        _registry.erase_entity(collidedEntity);
    }
}

void System::DamageSystem::createExplosion(Component::Position pos)
{
    engine::Entity explosion(_registry.get_new_entity());

    _registry.get_components<Component::Position>().insert_at(
        explosion, pos
    );
    _registry.get_components<Component::Drawable>().insert_at(
        explosion, Component::Drawable(
            EXPLOSION_INDEX ,EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 2
            )
    );
    _registry.get_components<Component::Animation>().insert_at(
        explosion, Component::Animation(
            EXPLOSION_WIDTH * EXPLOSION_FRAMES, EXPLOSION_HEIGHT,
            EXPLOSION_WIDTH, EXPLOSION_HEIGHT, EXPLOSION_WIDTH, 10
        )
    );
    _registry.get_components<Component::LifeTime>().insert_at(
        explosion, Component::LifeTime(40, _registry.getTick())
    );
}

void System::DamageSystem::createBigExplosion(Component::Position pos)
{
    engine::Entity explosion(_registry.get_new_entity());

    _registry.get_components<Component::Position>().insert_at(
        explosion, pos
    );
    _registry.get_components<Component::Drawable>().insert_at(
        explosion, Component::Drawable(
            BIG_EX_INDEX ,BIG_EX_WIDTH, BIG_EX_HEIGHT, 2
            )
    );
    _registry.get_components<Component::Animation>().insert_at(
        explosion, Component::Animation(
            BIG_EX_WIDTH * BIG_EX_FRAMES, BIG_EX_HEIGHT,
            BIG_EX_WIDTH, BIG_EX_HEIGHT, BIG_EX_WIDTH, 10
        )
    );
    _registry.get_components<Component::LifeTime>().insert_at(
        explosion, Component::LifeTime(40, _registry.getTick())
    );
}
