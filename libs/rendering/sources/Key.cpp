/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Key
*/

#include "Key.hpp"
#include "Components/Velocity.hpp"
#include "Events/Key.hpp"
#include "SparseArray.hpp"
#include "raylib.h"

rendering::system::Key::Key(
    event::EventQueue &events,
    SparseArray<Component::Controllable> &controllables,
    SparseArray<Component::Velocity> &velocities, std::size_t playerNumber
)
    : _events(events)
    , _controllables(controllables)
    , _velocities(velocities)
    , _playerNumber(playerNumber)
{
}

rendering::system::Key::~Key() = default;

#include <iostream>

void rendering::system::Key::operator()()
{
    Component::Velocity velocity;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_Z)) {
        velocity._vy -= 5.0f;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_Q)) {
        velocity._vx -= 5.0f;
    }
    if (IsKeyDown(KEY_S)) {
        velocity._vy += 5.0f;
    }
    if (IsKeyDown(KEY_D)) {
        velocity._vx += 5.0f;
    }
    if (IsKeyDown(KEY_SPACE)) {
        _events.addEvent<Event::Key>(KEY_SPACE);
        _events.update();
    }

    for (auto it = _velocities.begin(); it != _velocities.end(); ++it) {
        auto &controllable = _controllables[it.get_entity()];
        bool isControllable
            = controllable && controllable->_id == _playerNumber;

        if (not isControllable)
            continue;
        **it = velocity;
    }
}
