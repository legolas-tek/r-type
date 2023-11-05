/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Move System
*/

#include "Systems/MoveSystem.hpp"
#include "Events/Collision.hpp"

System::MoveSystem::MoveSystem(
    event::EventQueue &events, SparseArray<Component::Position> &positions,
    SparseArray<Component::Velocity> const &velocities,
    SparseArray<Component::Solid> const &solids,
    SparseArray<Component::Collision> const &collisions
)
    : _events(events)
    , _positions(positions)
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
        engine::Entity collidingEntity
            = getCollidingSolidEntity(it.get_entity());

        if (not vel)
            continue;
        if (vel->_vx > 0 and canMoveRight(it.get_entity(), collidingEntity)) {
            pos._x += vel->_vx;
        }
        if (vel->_vx < 0 and canMoveLeft(it.get_entity(), collidingEntity)) {
            pos._x += vel->_vx;
        }
        if (vel->_vy > 0 and canMoveDown(it.get_entity(), collidingEntity)) {
            pos._y += vel->_vy;
        }
        if (vel->_vy < 0 and canMoveUp(it.get_entity(), collidingEntity)) {
            pos._y += vel->_vy;
        }
    }
}

engine::Entity System::MoveSystem::getCollidingSolidEntity(engine::Entity entity
)
{
    if (not _solids[entity] or not _collisions[entity])
        return engine::Entity(0);

    for (auto &collision : _events.getEvents<event::Collision>()) {
        if (collision.entity == entity)
            return collision.secondEntity;
    }

    return engine::Entity(0);
}

bool System::MoveSystem::canMoveUp(
    engine::Entity entity, engine::Entity collidingEntity
)
{
    if (collidingEntity == 0 || not _positions[collidingEntity])
        return true;
    auto &collidingPos = _positions[collidingEntity];
    auto &entityPos = _positions[entity];

    if (collidingPos->_y < entityPos->_y)
        return false;
    return true;
}

bool System::MoveSystem::canMoveDown(
    engine::Entity entity, engine::Entity collidingEntity
)
{
    if (collidingEntity == 0 || not _positions[collidingEntity])
        return true;
    auto &collidingPos = _positions[collidingEntity];
    auto &entityPos = _positions[entity];

    if (collidingPos->_y > entityPos->_y)
        return false;
    return true;
}

bool System::MoveSystem::canMoveLeft(
    engine::Entity entity, engine::Entity collidingEntity
)
{
    if (collidingEntity == 0 || not _positions[collidingEntity])
        return true;
    auto &collidingPos = _positions[collidingEntity];
    auto &entityPos = _positions[entity];

    if (collidingPos->_x < entityPos->_x)
        return false;
    return true;
}

bool System::MoveSystem::canMoveRight(
    engine::Entity entity, engine::Entity collidingEntity
)
{
    if (collidingEntity == 0 || not _positions[collidingEntity])
        return true;
    auto &collidingPos = _positions[collidingEntity];
    auto &entityPos = _positions[entity];

    if (collidingPos->_x > entityPos->_x)
        return false;
    return true;
}
