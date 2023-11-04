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

#include "Events/Collision.hpp"
#include "Events/Death.hpp"

System::DeathAnimationManager::DeathAnimationManager(
    SparseArray<Component::Position> &positions,
    SparseArray<Component::Health> &healths,
    SparseArray<Component::Collision> &collisions,
    SparseArray<Component::Damage> &damages,
    SparseArray<Component::Controllable> &controllables, engine::Registry &reg
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
    for (auto &event : _registry.events) {
        auto death = dynamic_cast<event::Death *>(event.get());

        if (not death)
            continue;

        auto id = death->entity;
        auto &pos = _positions[id];

        if (not pos)
            continue;

        createBigExplosion(pos.value());
    }

    /*for (auto it = _collisions.begin(); it != _collisions.end(); it++) {
        auto id = it.get_entity();
        auto &pos = _positions[id];
        auto &damage = _damages[id];
        auto &controllable = _controllables[id];
        auto &health = _healths[id];

        if (not pos or not damage or controllable
            or not collision._collidingEntity)
            continue;

        engine::Entity collidingEntity = collision._collidingEntity.value();

        if (health and not _controllables[collidingEntity]) {
            continue;
        }
        createExplosion(pos.value());
        _registry.erase_entity(id);
    }*/
}

void System::DeathAnimationManager::createExplosion(
    Component::Position const &pos
)
{
    engine::Entity explosion(_registry.get_new_entity());

    _positions.insert_at(explosion, pos);
    _registry.get_components<Component::Drawable>().emplace_at(
        explosion, EXPLOSION_INDEX, EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 3
    );
    _registry.get_components<Component::Animation>().emplace_at(
        explosion, EXPLOSION_WIDTH * EXPLOSION_FRAMES, EXPLOSION_HEIGHT,
        EXPLOSION_WIDTH, EXPLOSION_HEIGHT, EXPLOSION_WIDTH, 10
    );
    _registry.get_components<Component::LifeTime>().emplace_at(
        explosion, 40, _registry.getTick()
    );
}

void System::DeathAnimationManager::createBigExplosion(Component::Position pos)
{
    engine::Entity explosion(_registry.get_new_entity());

    _positions.emplace_at(explosion, pos);
    _registry.get_components<Component::Drawable>().emplace_at(
        explosion, BIG_EX_INDEX, BIG_EX_WIDTH, BIG_EX_HEIGHT, 2
    );
    _registry.get_components<Component::Animation>().emplace_at(
        explosion, BIG_EX_WIDTH * BIG_EX_FRAMES, BIG_EX_HEIGHT, BIG_EX_WIDTH,
        BIG_EX_HEIGHT, BIG_EX_WIDTH, 10
    );
    _registry.get_components<Component::LifeTime>().emplace_at(
        explosion, 40, _registry.getTick()
    );
}
