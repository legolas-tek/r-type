/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Key
*/

#include "Components/Velocity.hpp"

#include "Events/KeyDown.hpp"
#include "Events/KeyPressed.hpp"
#include "Key.hpp"

#include "SparseArray.hpp"

#include "raylib.h"

#include <iostream>

constexpr KeyboardKey HANDLED_KEY[6]
    = { KEY_W, KEY_Z, KEY_A, KEY_Q, KEY_S, KEY_D };

rendering::system::Key::Key(
    event::EventQueue &events,
    SparseArray<Component::Controllable> &controllables,
    std::size_t playerNumber
)
    : _events(events)
    , _controllables(controllables)
    , _playerNumber(playerNumber)
{
}

rendering::system::Key::~Key() = default;

void rendering::system::Key::operator()()
{
    for (auto it = _controllables.begin(); it != _controllables.end(); ++it) {
        if ((*it)->_id != _playerNumber)
            continue;

        // for (char keyPressed = GetKeyPressed(); keyPressed != 0;) {
        //_events.addEvent<event::KeyPressed>(
        // it.get_entity(),
        // keyPressed
        //);
        //}

        for (int i = 0; i != 6; ++i) {
            if (IsKeyDown(HANDLED_KEY[i])) {
                _events.addEvent<event::KeyDown>(
                    it.get_entity(), HANDLED_KEY[i]
                );
            }
        }

        break;
    }
}
