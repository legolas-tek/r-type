/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** FollowSystem
*/

#include "Systems/FollowSystem.hpp"

System::FollowSystem::FollowSystem(
    SparseArray<Component::Follow> &follows,
    SparseArray<Component::Position> &positions, engine::Registry &reg
)
    : _follows(follows)
    , _positions(positions)
    , _reg(reg)
{
}

void System::FollowSystem::operator()()
{
    for (auto it = _follows.begin(); it != _follows.end(); it++) {
        auto follow = **it;

        if (_positions[it.get_entity()] && _positions[follow.targetEntity])
            continue;
        moveToTarget(
            follow,
            _positions[it.get_entity()].value(),
            _positions[follow.targetEntity].value()
        );
    }
}

void System::FollowSystem::moveToTarget(
    Component::Follow &ownerFollow,
    Component::Position &ownerPosition, Component::Position &targetPosition
)
{
    ownerPosition._x = targetPosition._x + ownerFollow.offsetX;
    ownerPosition._y = targetPosition._y + ownerFollow.offsetY;
}