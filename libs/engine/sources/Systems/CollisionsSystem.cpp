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
    for (auto it = _collisions.begin(); it != _collisions.end(); it++) {
        size_t i = it.get_entity();

        if (i == index)
            continue;

        auto &pos = _positions[i];

        if (!pos.has_value())
            continue;

        if (isColliding(
                _positions[index].value(), _hitboxes[index].value(),
                pos.value(), _collisions[i].value()
            )) {
            it->value()._collidingEntity = engine::Entity(index);
        }
    }
}

static void resetCollisions(SparseArray<Component::Collision> &collisions)
{
    for (auto it = collisions.begin(); it != collisions.end(); it++) {
        it->value()._collidingEntity = std::nullopt;
    }
}

void CollisionsSystem::operator()()
{
    resetCollisions(_collisions);
    for (auto it = _hitboxes.begin(); it != _hitboxes.end(); it++) {
        size_t index = it.get_entity();
        auto &pos = _positions[index];

        if (pos.has_value()) {
            checkCollisions(index);
        }
    }
}
