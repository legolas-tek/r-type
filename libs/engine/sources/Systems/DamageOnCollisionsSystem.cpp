/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DamageOnCollisionSystem
*/

#include "Events/Collision.hpp"
#include "Events/Damage.hpp"
#include "Systems/DamageOnCollisionSystem.hpp"

System::DamageOnCollisionSystem::DamageOnCollisionSystem(
    SparseArray<Component::Damage> &damages,
    SparseArray<Component::Health> &healths, event::EventQueue &eventQueue
)
    : _damages(damages)
    , _healths(healths)
    , _events(eventQueue)
{
}

void System::DamageOnCollisionSystem::operator()()
{
    for (auto &collision : _events.getEvents<event::Collision>()) {
        if (not _healths[collision.entity]
            or not _damages[collision.secondEntity])
            continue;

        if (_healths[collision.entity]->health <= 0)
            continue;

        _events.addEvent<event::Damage>(
            collision.entity, _damages[collision.secondEntity]->damages
        );
    }
}
