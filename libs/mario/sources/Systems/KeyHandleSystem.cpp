/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** KeyHandle
*/

#include "Systems/KeyHandleSystem.hpp"

#include "Events/Key.hpp"

#include <iostream>

#include "raylib.h"

System::KeyHandleSystem::KeyHandleSystem(Event::EventQueue &events)
    : _events(events)
{
}

void System::KeyHandleSystem::operator()()
{
    for (auto it = _events.beginIterator<Event::Key>();
         it != _events.endIterator<Event::Key>(); it++) {
        if (it->key == KEY_SPACE) {
            std::cout << "click sapace" << std::endl;
        }
    }
}
