/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DeathSystem
*/

#include "Systems/DeathSystem.hpp"

System::DeathSystem::DeathSystem(
    SparseArray<Component::Life> &lifes,
    engine::Registry &reg
)
    :_lifes(lifes)
    , _reg(reg)
{
}

void System::DeathSystem::operator()()
{
    for (auto it = _lifes.begin(); it != _lifes.end(); it++) {
        if ((*it)->life <= 0)
            _reg.erase_entity(it.get_entity());
    }
}
