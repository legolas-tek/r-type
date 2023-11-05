/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** JumpSystem
*/

#include "Systems/JumpSystem.hpp"

System::JumpSystem::JumpSystem(
    engine::Registry &reg, SparseArray<Component::Jump> &jumps,
    SparseArray<Component::Gravity> &gravities,
    SparseArray<Component::Velocity> &velocities
)
    : _reg(reg)
    , _jumps(jumps)
    , _gravities(gravities)
    , _velocities(velocities)
{
}

#include <iostream>

// TODO: can Jump if is on solid
bool System::JumpSystem::isOnSolid(engine::Entity jumpentity)
{
    return true;
}

void System::JumpSystem::operator()()
{
    for (auto it = _jumps.begin(); it != _jumps.end(); it++) {
        if (isOnSolid(it.get_entity())) {
            (*it)->canJump = true;
        }
        if ((*it)->isJumping) {
            if (_reg.getTick() - (*it)->startJumpTick < (*it)->jumpForTick) {
                _gravities[it.get_entity()]->isOffset = true;
                _velocities[it.get_entity()]->_vy -= 5;
            } else {
                _gravities[it.get_entity()]->isOffset = false;
                (*it)->isJumping = false;
            }
        }
    }
}
