/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ProcessKeyDownEvents system
*/

#include "Events/KeyDown.hpp"

#include "ProcessKeyDownEvents.hpp"

System::ProcessKeyDownEvents::ProcessKeyDownEvents(
    event::EventQueue &events, SparseArray<Component::Velocity> &velocities
)
    : _events(events)
    , _velocities(velocities)
{
}

void System::ProcessKeyDownEvents::operator()()
{
    for (auto &keyDown : _events.getEvents<event::KeyDown>()) {
        auto &velocities = _velocities[keyDown.entity];

        if (not velocities)
            continue;

        if (keyDown.key == 'W' or keyDown.key == 'Z')
            velocities->_vy -= 5.0f;
        else if (keyDown.key == 'S')
            velocities->_vy += 5.0f;
        else
            velocities->_vy = 0;

        if (keyDown.key == 'A' or keyDown.key == 'Q')
            velocities->_vx -= 5.0f;
        else if (keyDown.key == 'D')
            velocities->_vx += 5.0f;
        else
            velocities->_vx = 0;
    }
}
