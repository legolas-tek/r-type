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
    SparseArray<Component::Health> &healths, engine::Registry &reg
)
    : _positions(positions)
    , _healths(healths)
    , _registry(reg)
{
}

void System::DeathAnimationManager::operator()()
{
    for (auto &death : _registry.events.getEvents<event::Death>()) {
        auto &pos = _positions[death.entity];
        auto &health = _healths[death.entity];

        if (not pos)
            continue;

        if (health) {
            createBigExplosion(pos.value());
        } else {
            createExplosion(pos.value());
        }
    }
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
