/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Interpolation system
*/

#include "Interpolate.hpp"

net::Interpolate::Interpolate(
    SparseArray<Component::Velocity> &velocities,
    SparseArray<Component::Position> &positions
)
    : _velocities(velocities)
    , _positions(positions)
{
}

void net::Interpolate::operator()()
{
    for (auto it = _positions.begin(); it != _positions.end(); ++it) {
        auto &pos = **it;
        auto &vel = _velocities[it.get_entity()];

        vel->_vx = pos._futurX - pos._x / 2;
        vel->_vy = pos._futurY - pos._y / 2;
    }
}
