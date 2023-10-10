/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Move System
*/

#include "Systems/MoveSystem.hpp"

System::MoveSystem::MoveSystem(
    SparseArray<Component::Position> &positions,
    SparseArray<Component::Velocity> &velocities
)
    : _positions(positions)
    , _velocities(velocities)
{
}

void System::MoveSystem::operator()()
{
    auto pos_it = _positions.begin();
    auto vel_it = _velocities.begin();

    for (; pos_it != _positions.end() && vel_it != _velocities.end(); ++pos_it, ++vel_it) {
        auto &vel = _velocities[pos_it.get_entity()];

        if (vel.has_value()) {
            pos_it->value()._x += vel.value()._vx;
            pos_it->value()._y += vel.value()._vy;
        }
    }
}
