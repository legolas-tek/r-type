/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Close handler system
*/

#include "Systems/Close.hpp"
#include "GameLoop.hpp"

rendering::system::Close::Close(event::EventQueue &events)
    : _events(events)
{
}

void rendering::system::Close::operator()()
{
    for (auto close : _events.getEvents<event::Close>())
        throw GameEndException();
}
