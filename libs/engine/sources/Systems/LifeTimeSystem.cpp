/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** LifeTimeSystem
*/

#include "Systems/LifeTimeSystem.hpp"

System::LifeTimeSystem::LifeTimeSystem(
    SparseArray<Component::LifeTime> &life_times, engine::Registry &registry
)
    : _life_times(life_times)
    , _registry(registry)
{
}

void System::LifeTimeSystem::operator()()
{
    for (auto it = _life_times.begin(); it != _life_times.end(); it++) {
        if ((*it)->deathTick == _registry.getTick()) {
            _registry.erase_entity(it.get_entity());
        }
    }
}
