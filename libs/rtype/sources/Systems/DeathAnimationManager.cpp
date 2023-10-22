/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DeathAnimationManager
*/

#include "Systems/DeathAnimationManager.hpp"

#include "Components/Animation.hpp"
#include "Components/Drawable.hpp"
#include "Components/LifeTime.hpp"

System::DeathAnimationManager::DeathAnimationManager(
    SparseArray<Component::Health> &healths,
    SparseArray<Component::Collision> &collisions,
    SparseArray<Component::Damage> &damages, engine::Registry &reg
)
    : _healths(healths)
    , _registry(reg)
    , _collisions(collisions)
    , _damages(damages)
{
}

void System::DeathAnimationManager::operator()()
{
    for (auto it = _healths.begin(); it != _healths.end(); it++) {
        if ((*it)->health == 0) {
            createBigExplosion(
                _registry.get_components<Component::Position>()[it.get_entity()]
                    .value()
            );
        }
    }
    for (auto it = _collisions.begin(); it != _collisions.end(); it++) {
        if ((*it)->_collidingEntity && _damages[it.get_entity()]) {
            createExplosion(
                _registry.get_components<Component::Position>()[it.get_entity()]
                    .value()
            );
            _registry.erase_entity(it.get_entity());
        }
    }
}

void System::DeathAnimationManager::createExplosion(
    Component::Position const &pos
)
{
    engine::Entity explosion(_registry.get_new_entity());

    _registry.get_components<Component::Position>().insert_at(explosion, pos);
    _registry.get_components<Component::Drawable>().insert_at(
        explosion,
        Component::Drawable(
            EXPLOSION_INDEX, EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 3
        )
    );
    _registry.get_components<Component::Animation>().insert_at(
        explosion,
        Component::Animation(
            EXPLOSION_WIDTH * EXPLOSION_FRAMES, EXPLOSION_HEIGHT,
            EXPLOSION_WIDTH, EXPLOSION_HEIGHT, EXPLOSION_WIDTH, 10
        )
    );
    _registry.get_components<Component::LifeTime>().insert_at(
        explosion, Component::LifeTime(40, _registry.getTick())
    );
}

void System::DeathAnimationManager::createBigExplosion(Component::Position pos)
{
    engine::Entity explosion(_registry.get_new_entity());

    _registry.get_components<Component::Position>().insert_at(explosion, pos);
    _registry.get_components<Component::Drawable>().insert_at(
        explosion,
        Component::Drawable(BIG_EX_INDEX, BIG_EX_WIDTH, BIG_EX_HEIGHT, 2)
    );
    _registry.get_components<Component::Animation>().insert_at(
        explosion,
        Component::Animation(
            BIG_EX_WIDTH * BIG_EX_FRAMES, BIG_EX_HEIGHT, BIG_EX_WIDTH,
            BIG_EX_HEIGHT, BIG_EX_WIDTH, 10
        )
    );
    _registry.get_components<Component::LifeTime>().insert_at(
        explosion, Component::LifeTime(40, _registry.getTick())
    );
}
