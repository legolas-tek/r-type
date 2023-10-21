/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Editable System
*/

#include "Systems/Editable.hpp"
#include "raylib.h"

rendering::system::Editable::Editable(
    SparseArray<Component::Editable> &editables,
    SparseArray<Component::Focusable> &focusables,
    SparseArray<Component::Text> &texts
)
    : _editables(editables)
    , _focusables(focusables)
    , _texts(texts)
{
}

rendering::system::Editable::~Editable() = default;

void rendering::system::Editable::operator()()
{
    for (auto it = _editables.begin(); it != _editables.end(); ++it) {
        auto &focusable = _focusables[it.get_entity()];
        auto &text = _texts[it.get_entity()];

        if (not focusable or not text or not focusable->isFocused)
            continue;

        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (not text->_text.empty())
                text->_text.pop_back();
            continue;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            focusable->isFocused = false;
            continue;
        }

        int c = GetCharPressed();
        if (c == 0)
            continue;
        text->_text.push_back(char(c));
    }
}
