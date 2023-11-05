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

#include <iostream>

void rendering::system::Key::operator()()
{
    for (char key : HANDLED_KEY) {
        if (IsKeyDown(key)) {
            _events.addEvent<event::KeyDown>(key);
        }
    }
}
