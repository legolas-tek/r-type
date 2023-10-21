/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DeathSystem
*/

#include "Systems/DeathSystem.hpp"

System::DeathSystem::DeathSystem(
    SparseArray<Component::Life> &lifes, engine::Registry &reg
)
    : _lifes(lifes)
    , _reg(reg)
{
}

void System::DeathSystem::operator()()
{
    for (auto it = _lifes.begin(); it != _lifes.end(); it++) {
        auto target = std::find(
            _toEraseEntityList.begin(), _toEraseEntityList.end(),
            it.get_entity()
        );

        if (target != _toEraseEntityList.end()) {
            _reg.erase_entity(it.get_entity());
            continue;
        }
        if ((*it)->life <= 0)
            _toEraseEntityList.push_back(it.get_entity());
    }
}
