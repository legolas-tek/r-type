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
    SparseArray<Component::HurtBox> &hurtboxes
) : _positions(positions), _hitboxes(hitboxes), _hurtboxes(hurtboxes)
{
}

static bool isColliding(
    const Component::Position &pos,
    const Component::HitBox &hit,
    const Component::Position &hurtPos,
    const Component::HurtBox &hurt
)
{
    auto leftHitBox = pos._x - hit._width / 2;
    auto rightHitBox = pos._x + hit._width / 2;
    auto topHitBox = pos._y - hit._height / 2;
    auto bottomHitBox = pos._y + hit._height / 2;

    auto leftHurtBox = hurtPos._x - hurt._width / 2;
    auto rightHurtBox = hurtPos._x + hurt._width / 2;
    auto topHurtBox = hurtPos._y - hurt._height / 2;
    auto bottomHurtBox = hurtPos._y + hurt._height / 2;

    if (leftHitBox > rightHurtBox)
        return false;
    if (rightHitBox < leftHurtBox)
        return false;
    if (topHitBox < bottomHurtBox)
        return false;
    if (bottomHitBox > topHurtBox)
        return false;
    return true;
}

static void checkCollisions(
        SparseArray<Component::HurtBox> &hurtboxes,
        SparseArray<Component::Position> &positions,
        Component::Position &pos,
        Component::HitBox &hit)
{
    for (size_t i = 0; i < hurtboxes.size() && i < positions.size(); i++) {
        auto &hurt = hurtboxes[i];
        auto &hurtPos = positions[i];

        if (hurt && hurtPos && isColliding(pos, hit, hurtPos.value(), hurt.value()))
            std::cout << "Collision detected" << std::endl;
        }
}

void CollisionsSystem::operator()()
{
    for (size_t i = 0; i < _positions.size() && i < _hitboxes.size(); i++) {
        auto &pos = _positions[i];
        auto &hit = _hitboxes[i];

        if (pos && hit)
            checkCollisions(_hurtboxes, _positions, pos.value(), hit.value());
    }
}