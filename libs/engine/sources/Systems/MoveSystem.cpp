/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Move System
*/

#include "Systems/MoveSystem.hpp"

MoveSystem::MoveSystem(
    SparseArray<Component::Position> &positions,
    SparseArray<Component::Velocity> const &velocities
)
    : _positions(positions)
    , _velocities(velocities)
{
}

void MoveSystem::operator()()
{
    for (size_t i = 0; i < _positions.size() && i < _velocities.size(); i++) {
        auto &pos = _positions[i];
        auto &vel = _velocities[i];

        if (pos && vel) {
            pos.value()._x += vel.value()._vx;
            pos.value()._y += vel.value()._vy;
        }
    }
}
