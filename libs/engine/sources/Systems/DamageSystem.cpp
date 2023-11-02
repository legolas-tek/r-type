/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DamageSystem
*/

#include "Systems/DamageSystem.hpp"
#include "Events/Collision.hpp"
#include "Events/Death.hpp"

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
    for (auto it
         = _registry.events
               .eventIteratorBegin<std::unique_ptr<Event::Collision>>()) {
        auto collision = dynamic_cast<Event::Collision *>(event.get());

        if (not collision)
            continue;

        if (not _healths[collision->entity]
            or not _damages[collision->secondEntity])
            continue;

        if (_healths[collision->entity]->health <= 0)
            continue;

        _healths[collision->entity]->health
            -= _damages[collision->secondEntity]->damages;
    }
}
