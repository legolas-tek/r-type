/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DamageSystem
*/

#include "Systems/DamageSystem.hpp"
#include "Events/Collision.hpp"

System::DamageSystem::DamageSystem(
    SparseArray<Component::Damage> &damages,
    SparseArray<Component::Health> &healths,
    SparseArray<Component::Collision> &collisions, engine::Registry &registry
)
    : _damages(damages)
    , _healths(healths)
    , _collisions(collisions)
    , _registry(registry)
{
}

void System::DamageSystem::operator()()
{
    for (auto &event : _registry.events) {
        if (event->getType() != Event::EventType::COLLISION)
            continue;

        auto &collision = (Event::Collision &) *event;

        if (not _healths[collision.entity]
            or not _damages[collision.secondEntity])
            continue;

        if (_healths[collision.entity]->health <= 0)
            continue;

        _healths[collision.entity]->health
            -= _damages[collision.secondEntity]->damages;
    }
}
