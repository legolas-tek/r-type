/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ProcessKeyDownEvents system
*/

#include "Events/KeyDown.hpp"

#include "Systems/ProcessKeyDownEvents.hpp"

System::ProcessKeyDownEvents::ProcessKeyDownEvents(
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

void System::ProcessKeyDownEvents::operator()()
{
    Component::Velocity res;

    for (auto &keyDown : _events.getEvents<event::KeyDown>()) {

        if (keyDown.key == 'S') {
            res._vy += 5.0f;
        }

        if (keyDown.key == 'A' or keyDown.key == 'Q')
            res._vx -= 5.0f;

        if (keyDown.key == 'D')
            res._vx += 5.0f;
    }

    for (auto it = _velocities.begin(); it != _velocities.end(); ++it) {
        auto &controllable = _controllables[it.get_entity()];
        bool isControllable
            = controllable && controllable->_id == _playerNumber;

        if (not isControllable)
            continue;
        **it = res;
    }
}
