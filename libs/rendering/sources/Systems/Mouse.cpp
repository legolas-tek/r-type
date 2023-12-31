/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Mouse
*/

#include "Systems/Mouse.hpp"
#include "Events/Mouse.hpp"
#include "raylib.h"

rendering::system::Mouse::Mouse(event::EventQueue &events)
    : _events(events)
{
}

void rendering::system::Mouse::operator()()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        _events.addEvent<event::Mouse>(
            GetMousePosition().x, GetMousePosition().y,
            event::MouseEventType::LEFT
        );
    else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        _events.addEvent<event::Mouse>(
            GetMousePosition().x, GetMousePosition().y,
            event::MouseEventType::RIGHT
        );
    else if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON))
        _events.addEvent<event::Mouse>(
            GetMousePosition().x, GetMousePosition().y,
            event::MouseEventType::MIDDLE
        );
}
