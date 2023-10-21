/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Move System
*/

#include "Systems/MoveSystem.hpp"

System::MoveSystem::MoveSystem(
    SparseArray<Component::Position> &positions,
    SparseArray<Component::Velocity> const &velocities
)
    : _positions(positions)
    , _velocities(velocities)
{
}

void System::MoveSystem::operator()()
{
    for (auto it = _positions.begin(); it != _positions.end(); ++it) {
        auto &pos = **it;
        auto &vel = _velocities[it.get_entity()];

        if (vel) {
            pos._x += vel->_vx;
            pos._y += vel->_vy;
        }
    }
}
