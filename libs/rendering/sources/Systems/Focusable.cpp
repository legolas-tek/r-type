/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Focusable System
*/

#include "Systems/Focusable.hpp"
#include "Events/Mouse.hpp"
#include "raylib.h"

rendering::system::Focusable::Focusable(
    Event::EventQueue &events, SparseArray<Component::Focusable> &focusables,
    SparseArray<Component::HitBox> &hitboxes,
    SparseArray<Component::Position> &positions
)
    : _events(events)
    , _focusables(focusables)
    , _hitboxes(hitboxes)
    , _positions(positions)
{
}

rendering::system::Focusable::~Focusable() = default;

void rendering::system::Focusable::operator()()
{
    for (auto click = _events.beginIterator<Event::Mouse>();
         click != _events.endIterator<Event::Mouse>(); ++click) {
        for (auto it = _focusables.begin(); it != _focusables.end(); ++it) {
            size_t index = it.get_entity();

            auto &hitbox = _hitboxes[index];
            auto &position = _positions[index];

            if (not hitbox or not position)
                continue;

            auto rect = Rectangle { position->_x - hitbox->_width / 2,
                                    position->_y - hitbox->_height / 2,
                                    hitbox->_width, hitbox->_height };

            (*it)->isFocused
                = CheckCollisionPointRec({ click->x, click->y }, rect);
        }
    }
}
