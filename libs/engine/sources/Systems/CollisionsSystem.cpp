/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Collisions System
*/

#include "Systems/CollisionsSystem.hpp"
#include "Events/Collision.hpp"

System::CollisionsSystem::CollisionsSystem(
    event::EventQueue &events, SparseArray<Component::Position> &positions,
    SparseArray<Component::HitBox> &hitboxes,
    SparseArray<Component::Collision> &collisions
)
    : _events(events)
    , _positions(positions)
    , _hitboxes(hitboxes)
    , _collisions(collisions)
{
}

static bool isColliding(
    Component::Position const &pos, Component::HitBox const &hit,
    Component::Position const &hurtPos, Component::Collision const &hurt
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
    if (topHitBox > bottomCollision)
        return false;
    if (bottomHitBox < topCollision)
        return false;
    return true;
}

void System::CollisionsSystem::checkCollisions(size_t index)
{
    for (auto it = _collisions.begin(); it != _collisions.end(); it++) {
        size_t i = it.get_entity();

        if (i == index)
            continue;

        auto &pos = _positions[i];

        if (not pos.has_value())
            continue;

        if (isColliding(
                _positions[index].value(), _hitboxes[index].value(),
                pos.value(), _collisions[i].value()
            )) {
            _events.addEvent<event::Collision>(
                engine::Entity(index), engine::Entity(i)
            );
        }
    }
}

void System::CollisionsSystem::operator()()
{
    for (auto it = _hitboxes.begin(); it != _hitboxes.end(); it++) {
        size_t index = it.get_entity();
        auto &pos = _positions[index];

        if (pos.has_value()) {
            checkCollisions(index);
        }
    }
}
