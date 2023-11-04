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
    SparseArray<Component::Life> &lifes, engine::Registry &reg
)
    : _healths(healths)
    , _registry(reg)
    , _lifes(lifes)
{
}

bool isEntityInDeathEvent(engine::Entity entity, event::EventQueue &queue)
{
    for (auto &death : queue.getEvents<event::Death>()) {
        if (death.entity == entity)
            return true;
    }
    return false;
}

void System::DeathSystem::operator()()
{
    // Tant qu'il n'y a pas de réseau sur les events, on ne peut pas erase sur
    // la meme frame
    /*for (auto &death : _events.getEvents<event::Death>()) {
        _registry.erase_entity(death.entity);
    }*/
    for (auto it = _healths.begin(); it != _healths.end(); it++) {
        int lifes = 0;

        if (_lifes[it.get_entity()])
            lifes = _lifes[it.get_entity()]->lifes;

        if (isEntityInDeathEvent(it.get_entity(), _events)) {
            _registry.erase_entity(it.get_entity());
            continue;
        }

        if ((*it)->health <= 0 && lifes <= 0)
            _events.addEvent<event::Death>(it.get_entity());
    }
}
