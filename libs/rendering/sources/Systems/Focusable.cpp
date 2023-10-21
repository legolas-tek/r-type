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

    auto pos = GetMousePosition();

    for (auto it = _focusables.begin(); it != _focusables.end(); ++it) {
        size_t index = it.get_entity();

        if (not _hitboxes[index].has_value())
            continue;

        auto &hitbox = _hitboxes[index];
        auto &position = _positions[index];
        auto Rect = Rectangle { position->_x, position->_y, hitbox->_width,
                                hitbox->_height };

        if (CheckCollisionPointRec(pos, Rect)) {
            it->value().isFocusable = true;
        } else {
            it->value().isFocusable = false;
        }
    }
}
