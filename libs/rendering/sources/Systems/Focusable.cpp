/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Focusable System
*/

#include "Systems/Focusable.hpp"
#include "raylib.h"

rendering::system::Focusable::Focusable(
    SparseArray<Component::Focusable> &focusables,
    SparseArray<Component::HitBox> &hitboxes,
    SparseArray<Component::Position> &positions
)
    : _focusables(focusables)
    , _hitboxes(hitboxes)
    , _positions(positions)
{
}

rendering::system::Focusable::~Focusable() = default;

void rendering::system::Focusable::operator()()
{
    if (not IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        return;

    auto mousePosition = GetMousePosition();

    for (auto it = _focusables.begin(); it != _focusables.end(); ++it) {
        size_t index = it.get_entity();

        auto &hitbox = _hitboxes[index];
        auto &position = _positions[index];

        if (not hitbox.has_value() or not position.has_value())
            continue;

        auto rect = Rectangle { position->_x - hitbox->_width / 2,
                                position->_y - hitbox->_height / 2,
                                hitbox->_width, hitbox->_height };

        it->value().isFocused = CheckCollisionPointRec(mousePosition, rect);
    }
}
