/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ProcessKeyDownEvents system
*/

#include "Events/KeyDown.hpp"

#include "ProcessKeyDownEvents.hpp"

#include <iostream>

System::ProcessKeyDownEvents::ProcessKeyDownEvents(
    event::EventQueue &events, SparseArray<Component::Velocity> &velocities
)
    : _events(events)
    , _velocities(velocities)
{
}

void System::ProcessKeyDownEvents::operator()()
{
    Component::Velocity res;

    for (auto &keyDown : _events.getEvents<event::KeyDown>()) {
        auto &velocities = _velocities[keyDown.entity];

        if (not velocities)
            continue;

        if (keyDown.key == 'W' or keyDown.key == 'Z')
            res._vy -= 5.0f;

        if (keyDown.key == 'S')
            res._vy += 5.0f;

        if (keyDown.key == 'A' or keyDown.key == 'Q')
            res._vx -= 5.0f;

        if (keyDown.key == 'D')
            res._vx += 5.0f;

        velocities = res;
        keyDown.key = 0;
    }
}
