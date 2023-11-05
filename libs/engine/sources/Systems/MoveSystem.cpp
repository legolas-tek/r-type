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

        if (vel && canMoveX(it.get_entity(), collidingEntity)) {
            pos._x += vel->_vx;
        }
        if (vel && canMoveY(it.get_entity(), collidingEntity)) {
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

bool System::MoveSystem::canMoveX(
    engine::Entity entity, engine::Entity collidingEntity
)
{
    if (collidingEntity == 0 or not _positions[collidingEntity]
        or not _solids[collidingEntity] or not _collisions[entity])
        return true;

    Component::Position &entityPos = _positions[entity].value();
    Component::Position &collidingEntityPos
        = _positions[collidingEntity].value();

    Component::Collision const &entityCollision = _collisions[entity].value();
    Component::Collision const &collidingEntityCollision
        = _collisions[collidingEntity].value();

    Component::Velocity const &entityVelocity = _velocities[entity].value();
    Component::Velocity const &collidingEntityVelocity
        = _velocities[collidingEntity].value();

    float entityPosTop = entityPos._y - entityCollision._height / 2;
    float entityPosBottom = entityPos._y + entityCollision._height / 2;

    float collidingEntityPosTop
        = collidingEntityPos._y - collidingEntityCollision._height / 2;
    float collidingEntityPosBottom
        = collidingEntityPos._y + collidingEntityCollision._height / 2;

    bool isInY1 = entityPosTop < collidingEntityPosTop
        && collidingEntityPosTop < entityPosBottom;
    bool isInY2 = entityPosTop < collidingEntityPosBottom
        && collidingEntityPosBottom < entityPosBottom;

    // TODO: 오른쪽 맨 끝이면 / 왼쪽 맨 끝이면
    // if Y don't overlap, can go X
    if (isInY1 || isInY2) {
        return true;
    }

    float entityLeft = entityPos._x - (entityCollision._width / 2);
    float entityRight = entityPos._x + (entityCollision._width / 2);

    float collidingEntityLeft
        = collidingEntityPos._x - (collidingEntityCollision._width / 2);
    float collidingEntityRight
        = collidingEntityPos._x + (collidingEntityCollision._width / 2);
    if (entityRight < collidingEntityLeft && 0 < entityVelocity._vx) {
        return false;
    }
    if (collidingEntityRight < entityLeft && entityVelocity._vx < 0) {
        return false;
    }
    return true;
}

bool System::MoveSystem::canMoveY(
    engine::Entity entity, engine::Entity collidingEntity
)
{
    if (collidingEntity == 0 or not _positions[collidingEntity]
        or not _solids[collidingEntity] or not _collisions[entity])
        return true;

    Component::Position &entityPos = _positions[entity].value();
    Component::Position &collidingEntityPos
        = _positions[collidingEntity].value();

    Component::Collision const &entityCollision = _collisions[entity].value();
    Component::Collision const &collidingEntityCollision
        = _collisions[collidingEntity].value();

    Component::Velocity const &entityVelocity = _velocities[entity].value();
    Component::Velocity const &collidingEntityVelocity
        = _velocities[collidingEntity].value();

    float entityPosLeft = entityPos._x - entityCollision._width / 2;
    float entityPosRight = entityPos._x + entityCollision._width / 2;

    float collidingEntityPosLeft
        = collidingEntityPos._x - collidingEntityCollision._width / 2;
    float collidingEntityPosRight
        = collidingEntityPos._x + collidingEntityCollision._width / 2;

    bool isInX1 = entityPosLeft < collidingEntityPosLeft
        && collidingEntityPosLeft < entityPosRight;
    bool isInX2 = entityPosLeft < collidingEntityPosRight
        && collidingEntityPosRight < entityPosRight;

    if (isInX1 || isInX2) {
        return true;
    }

    if (entityPos._y < collidingEntityPos._y && 0 < entityVelocity._vy) {
        return false;
    }
    if (entityPos._y > collidingEntityPos._y && 0 < entityVelocity._vy) {
        return false;
    }
    return true;
}
