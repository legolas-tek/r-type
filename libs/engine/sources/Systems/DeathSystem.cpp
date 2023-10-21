/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DeathSystem
*/

#include "Systems/DeathSystem.hpp"

System::DeathSystem::DeathSystem(
    SparseArray<Component::Health> &healths, engine::Registry &reg
)
    : _healths(healths)
    , _reg(reg)
{
}

void System::DeathSystem::operator()()
{
    for (auto it = _healths.begin(); it != _healths.end(); it++) {
        if ((*it)->health <= 0)
            _reg.erase_entity(it.get_entity());
    }
}
