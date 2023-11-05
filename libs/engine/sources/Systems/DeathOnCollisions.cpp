/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DeathOnCollisions
*/

#include "Systems/DeathOnCollisions.hpp"

#include "Events/Collision.hpp"
#include "Events/Death.hpp"

System::DeathOnCollisions::DeathOnCollisions(
        SparseArray<Component::Solid> &solids,
        SparseArray<Component::KillOnCollision> &killOnCollisions,
        event::EventQueue &events
)
    : _solids(solids)
    , _killOnCollisions(killOnCollisions)
    , _events(events)
{
}

void System::DeathOnCollisions::operator()()
{
    for (auto &collision : _events.getEvents<event::Collision>()) {
        if (_killOnCollisions[collision.entity] and
            _solids[collision.secondEntity] and
            not isAlreadyInDeathEvent(collision.entity)) {
            _events.addEvent<event::Death>(collision.entity);
        }
    }
}


bool System::DeathOnCollisions::isAlreadyInDeathEvent(engine::Entity entity) const
{
    for (auto &death : _events.getEvents<event::Death>()) {
        if (death.entity == entity) {
            return true;
        }
    }
    return false;
}
