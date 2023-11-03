/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DamageOnCollisionSystem
*/

#include "Events/Collision.hpp"
#include "Events/Damage.hpp"
#include "Systems/DamageOnCollisionSystem.hpp"

#include <iostream>

System::DamageOnCollisionSystem::DamageOnCollisionSystem(
    SparseArray<Component::Damage> &damages,
    SparseArray<Component::Health> &healths, Event::EventQueue &eventQueue
)
    : _damages(damages)
    , _healths(healths)
    , _events(eventQueue)
{
}

void System::DamageOnCollisionSystem::operator()()
{
    for (auto it = _events.beginIterator<Event::Collision>();
         it != _events.endIterator<Event::Collision>(); it++) {
        auto collision = dynamic_cast<Event::Collision *>(it->get());

        if (not _healths[collision->entity]
            or not _damages[collision->secondEntity])
            continue;

        if (_healths[collision->entity]->health <= 0)
            continue;

        _events.addEvent<Event::Damage>(
            collision->entity, _damages[collision->secondEntity]->damages
        );
    }
    _events.update();
}
