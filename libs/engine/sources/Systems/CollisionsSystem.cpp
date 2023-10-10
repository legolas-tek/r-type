/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Collisions System
*/

#include "Systems/CollisionsSystem.hpp"

CollisionsSystem::CollisionsSystem(
    SparseArray<Component::Position> &positions,
    SparseArray<Component::HitBox> &hitboxes,
    SparseArray<Component::Collision> &collisions
) : _positions(positions), _hitboxes(hitboxes), _collisions(collisions)
{
}

static bool isColliding(
    const Component::Position &pos,
    const Component::HitBox &hit,
    const Component::Position &hurtPos,
    const Component::Collision &hurt
)
{
    float leftHitBox = pos._x - hit._width / 2;
    float rightHitBox = pos._x + hit._width / 2;
    float topHitBox = pos._y - hit._height / 2;
    float bottomHitBox = pos._y + hit._height / 2;

    float leftCollision = hurtPos._x - hurt._width / 2;
    float rightCollision = hurtPos._x + hurt._width / 2;
    float topCollision = hurtPos._y - hurt._height / 2;
    float bottomCollision = hurtPos._y + hurt._height / 2;

    if (leftHitBox > rightCollision)
        return false;
    if (rightHitBox < leftCollision)
        return false;
    if (topHitBox < bottomCollision)
        return false;
    if (bottomHitBox > topCollision)
        return false;
    return true;
}

void CollisionsSystem::checkCollisions(size_t index)
{
    for (auto it = _hitboxes.begin(); it != _hitboxes.end(); it++) {
        size_t i = it.get_entity();

        if (i == index)
            continue;

        auto &pos = _positions[i];
        auto &collision = _collisions[i];

        if (!pos.has_value() || !collision.has_value())
            continue;

        if (isColliding(_positions[index].value(),
                        _hitboxes[index].value(),
                        pos.value(),
                        collision.value())) {
            collision.value()._isColliding = true;
            collision.value()._collidingEntity = engine::Entity(index);
            _collisions[index].value()._isColliding = true;
            _collisions[index].value()._collidingEntity = engine::Entity(i);
        }
    }
}

void CollisionsSystem::operator()()
{
    for (auto it = _hitboxes.begin(); it != _hitboxes.end(); it++) {
        size_t index = it.get_entity();
        auto &pos = _positions[index];
        auto &collision = _collisions[index];

        if (pos.has_value() && collision.has_value()) {
            checkCollisions(index);
        }
    }
}