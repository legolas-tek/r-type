/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DamageSystem
*/

#include "Systems/DamageSystem.hpp"
#include "Events/Collision.hpp"
#include "Events/Death.hpp"

#include <iostream>

System::DamageSystem::DamageSystem(
    SparseArray<Component::Damage> &damages,
    SparseArray<Component::Health> &healths, Event::EventQueue &eventQueue
)
    : _damages(damages)
    , _healths(healths)
    , _events(eventQueue)
{
}

void System::DamageSystem::operator()()
{
    for (auto it = _events.beginIterator<Event::Collision>();
         it != _events.endIterator<Event::Collision>(); it++) {
        auto collision = dynamic_cast<Event::Collision *>(it->get());

        if (not _healths[collision->entity]
            or not _damages[collision->secondEntity])
            continue;

        if (_healths[collision->entity]->health <= 0)
            continue;

        _healths[collision->entity]->health
            -= _damages[collision->secondEntity]->damages;
    }
}
