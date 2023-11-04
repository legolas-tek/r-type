/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** FloatingSystem
*/

#include "Systems/FloatingSystem.hpp"

System::FloatingSystem::FloatingSystem(
    SparseArray<Component::Position> &positions,
    SparseArray<Component::Velocity> &velocities,
    SparseArray<Component::Floating> &floatings
)
    : _positions(positions)
    , _velocities(velocities)
    , _floatings(floatings)
{
}

void System::FloatingSystem::operator()()
{
    for (auto it = _floatings.begin(); it != _floatings.end(); it++) {
        engine::Entity target = it.get_entity();
        auto &floating = **it;
        auto &position = _positions[target];
        auto &velocity = _velocities[target];

        if (!position || !velocity)
            continue;
        adaptVelocity(position.value(), velocity.value(), floating);
    }
}

void System::FloatingSystem::adaptVelocity(
    Component::Position &position, Component::Velocity &velocity,
    Component::Floating &floating
)
{
    if (velocity._vx >= 0 and position._x >= floating.maxX) {
        velocity._vx = -floating.speed;
    }
    if (velocity._vx <= 0 and position._x <= floating.minX) {
        velocity._vx = floating.speed;
    }
    if (velocity._vy >= 0 and position._y >= floating.maxY) {
        velocity._vy = -floating.speed;
    }
    if (velocity._vy <= 0 and position._y <= floating.minY) {
        velocity._vy = floating.speed;
    }
}
