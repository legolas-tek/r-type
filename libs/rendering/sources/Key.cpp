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

constexpr KeyboardKey HANDLED_DOWN_KEY[6]
    = { KEY_W, KEY_Z, KEY_A, KEY_Q, KEY_S, KEY_D };

constexpr KeyboardKey HANDLED_PRESSED_KEY[6] = { KEY_L, KEY_P };

rendering::system::Key::Key(event::EventQueue &events)
    : _events(events)
{
}

rendering::system::Key::~Key() = default;

void rendering::system::Key::operator()()
{
    for (char key : HANDLED_DOWN_KEY) {
        if (IsKeyDown(key)) {
            _events.addEvent<event::KeyDown>(key);
        }
    }

    for (char key : HANDLED_PRESSED_KEY) {
        if (IsKeyPressed(key)) {
            _events.addEvent<event::KeyPressed>(key);
        }
    }
}
