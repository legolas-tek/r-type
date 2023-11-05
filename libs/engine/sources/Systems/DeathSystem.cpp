/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DeathSystem
*/

#include "Systems/DeathSystem.hpp"
#include "Events/Death.hpp"

System::DeathSystem::DeathSystem(
    SparseArray<Component::Health> &healths,
    SparseArray<Component::Life> &lifes,
    SparseArray<Component::Dependent> &dependents,
    SparseArray<Component::Follow> &follows, engine::Registry &reg
)
    : _healths(healths)
    , _lifes(lifes)
    , _dependents(dependents)
    , _follows(follows)
    , _registry(reg)
{
}

void System::DeathSystem::operator()()
{
    for (auto &death : _registry.events.getEvents<event::Death>()) {
        _registry.erase_entity(death.entity);
    }
    for (auto it = _healths.begin(); it != _healths.end(); it++) {
        int lifes = 0;

        if (_lifes[it.get_entity()])
            lifes = _lifes[it.get_entity()]->lifes;

        if ((*it)->health <= 0 and lifes <= 0 and
            not isAlreadyInDeathEvent(it.get_entity())) {
            _events.addEvent<event::Death>(it.get_entity());
            eraseDependentsEntities(it.get_entity());
        }
    }
}

void System::DeathSystem::eraseDependentsEntities(engine::Entity entity)
{
    for (auto it = _dependents.begin(); it != _dependents.end(); it++) {
        if ((*it)->targetEntity == entity) {
            _registry.events.addEvent<event::Death>(it.get_entity());
        }
    }
    for (auto it = _follows.begin(); it != _follows.end(); it++) {
        if ((*it)->targetEntity == entity) {
            _registry.events.addEvent<event::Death>(it.get_entity());
        }
    }
}

bool System::DeathSystem::isAlreadyInDeathEvent(engine::Entity entity) const
{
    for (auto &death : _registry.events.getEvents<event::Death>()) {
        if (death.entity == entity) {
            return true;
        }
    }
    return false;
}
