/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Move System
*/

#include "Systems/MoveSystem.hpp"

System::MoveSystem::MoveSystem(
    SparseArray<Component::Position> &positions,
    SparseArray<Component::Velocity> const &velocities,
    SparseArray<Component::Solid> const &solids,
    SparseArray<Component::Collision> const &collisions
)
    : _positions(positions)
    , _velocities(velocities)
    , _solids(solids)
    , _collisions(collisions)
{
}

void System::MoveSystem::operator()()
{
    for (auto it = _positions.begin(); it != _positions.end(); ++it) {
        auto &pos = **it;
        auto &vel = _velocities[it.get_entity()];
        auto &solid = _solids[it.get_entity()];

        if (vel) {
            pos._x += vel->_vx;
            pos._y += vel->_vy;
        }
    }
}

engine::Entity System::MoveSystem::getCollidingSolidEntity(
    engine::Entity entity
)
{
    if (_solids[entity] || !_collisions[entity] ||
        !_collisions[entity]->_collidingEntity)
        return engine::Entity(0);
    return engine::Entity(0);
}
