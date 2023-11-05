/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Restart System
*/

#include "Restart.hpp"
#include "Events/Mouse.hpp"
#include "GameLoop.hpp"

System::Restart::Restart(
    event::EventQueue &events,
    SparseArray<Component::RestartOnClick> &controllables,
    SparseArray<Component::Focusable> &focusables
)
    : _events(events)
    , _restarts(controllables)
    , _focusables(focusables)
{
}

void System::Restart::operator()()
{
    for (auto it = _restarts.begin(); it != _restarts.end(); it++) {
        auto index = it.get_entity();
        auto &focusable = _focusables[index];

        if (not focusable)
            continue;
        if (not focusable->isFocused)
            continue;

        throw GameEndException();
    }
}
