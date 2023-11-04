/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** JumpSystem
*/

#include "Systems/JumpSystem.hpp"

System::JumpSystem::JumpSystem(
    engine::Registry &reg, SparseArray<Component::Jump> &jumps,
    SparseArray<Component::Gravity> &gravities
)
    : _reg(reg)
    , _jumps(jumps)
    , _gravities(gravities)
{
}

#include <iostream>

void System::JumpSystem::operator()()
{
    for (auto it = _jumps.begin(); it != _jumps.end(); it++) {
        if ((*it)->isJumping) {
            if (_reg.getTick() - (*it)->startJumpTick < (*it)->jumpForTick) {
                _gravities[it.get_entity()]->isOffset = true;
            } else {
                _gravities[it.get_entity()]->isOffset = false;
            }
        }
    }
}
