/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Close handler system
*/

#include "Systems/Close.hpp"
#include "GameLoop.hpp"

rendering::system::Close::Close(Event::EventQueue &events)
    : _events(events)
{
}

void rendering::system::Close::operator()()
{
    if (_events.hasEvent<Event::Close>())
        throw GameEndException();
}
