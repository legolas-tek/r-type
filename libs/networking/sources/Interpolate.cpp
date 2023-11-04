/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Interpolation system
*/

#include "Interpolate.hpp"

#include <iostream>

net::Interpolate::Interpolate(SparseArray<Component::Velocity> &velocities)
    : _velocities(velocities)
{
}

void net::Interpolate::operator()()
{
    for (auto &it : _velocities) {
        if (it->_futurVx == 0 or it->_futurVy == 0)
            continue;

        it->_vx += (it->_futurVx / 8);
        it->_vy += (it->_futurVy / 8);
    }
}
