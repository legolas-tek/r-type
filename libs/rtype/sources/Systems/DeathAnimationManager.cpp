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
    SparseArray<Component::Position> &positions,
    SparseArray<Component::Health> &healths,
    SparseArray<Component::Collision> &collisions,
    SparseArray<Component::Damage> &damages,
    SparseArray<Component::Controllable> &controllables,
    engine::Registry &reg
)
    : _positions(positions)
    , _healths(healths)
    , _registry(reg)
    , _collisions(collisions)
    , _damages(damages)
    , _controllables(controllables)
{
}

void System::DeathAnimationManager::operator()()
{
    for (auto it = _healths.begin(); it != _healths.end(); it++) {
        auto &health = **it;
        auto &pos = _positions[it.get_entity()];

        if (not pos.has_value())
            continue;

        if (health.health == 0) {
            createBigExplosion(pos.value());
        }
    }

    for (auto it = _collisions.begin(); it != _collisions.end(); it++) {
        auto &collision = **it;
        auto id = it.get_entity();
        auto &pos = _positions[id];
        auto &damage = _damages[id];
        auto &controllable = _controllables[id];
        if (not pos or not damage or controllable)
            continue;

        if (collision._collidingEntity) {
            createExplosion(pos.value());
            _registry.erase_entity(id);
        }
    }
}

void System::DeathAnimationManager::createExplosion(
    Component::Position const &pos
)
{
    engine::Entity explosion(_registry.get_new_entity());

    _positions.insert_at(explosion, pos);
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

    _positions.insert_at(explosion, pos);
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
