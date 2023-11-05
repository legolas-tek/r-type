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

constexpr KeyboardKey HANDLED_KEY[6]
    = { KEY_W, KEY_Z, KEY_A, KEY_Q, KEY_S, KEY_D };

rendering::system::Key::Key(event::EventQueue &events)
    : _events(events)
{
}

rendering::system::Key::~Key() = default;

void rendering::system::Key::operator()()
{
    // for (char keyPressed = GetKeyPressed(); keyPressed != 0;) {
    //_events.addEvent<event::KeyPressed>(
    // keyPressed
    //);
    //}

    for (int i = 0; i != 6; ++i) {
        if (IsKeyDown(HANDLED_KEY[i])) {
            _events.addEvent<event::KeyDown>(HANDLED_KEY[i]);
        }
    }
}
