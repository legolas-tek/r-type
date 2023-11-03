/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DeathSystem
*/

#include "Systems/DeathSystem.hpp"

System::DeathSystem::DeathSystem(
    SparseArray<Component::Health> &healths,
    SparseArray<Component::Life> &lifes, engine::Registry &reg
)
    : _healths(healths)
    , _reg(reg)
    , _lifes(lifes)
{
}

void System::DeathSystem::operator()()
{
    for (auto it = _healths.begin(); it != _healths.end(); it++) {
        auto target = std::find(
            _toEraseEntityList.begin(), _toEraseEntityList.end(),
            it.get_entity()
        );
        int lifes = 0;

        if (_lifes[it.get_entity()])
            lifes = _lifes[it.get_entity()]->lifes;

        if (target != _toEraseEntityList.end()) {
            _reg.erase_entity(it.get_entity());
            _toEraseEntityList.erase(target);
            continue;
        }
        if ((*it)->health <= 0 && lifes <= 0) {
            _toEraseEntityList.push_back(it.get_entity());
        }
    }
}
