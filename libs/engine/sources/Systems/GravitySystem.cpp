/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GravitySystem
*/

#include "Systems/GravitySystem.hpp"

System::GravitySystem::GravitySystem(
    SparseArray<Component::Gravity> &gravities,
    SparseArray<Component::Velocity> &velocities
)
    : _gravities(gravities)
    , _velocities(velocities)
{
}

void System::GravitySystem::operator()()
{
    for (auto it = _gravities.begin(); it != _gravities.end(); it++) {
        if ((*it)->isOffset == false) {
            _velocities[it.get_entity()]->_vy = 5;
        }
    }
}
