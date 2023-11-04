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

#include "Components/Jump.hpp"

System::KeyHandleSystem::KeyHandleSystem(
    engine::Registry &reg, Event::EventQueue &events
)
    : _reg(reg)
    , _events(events)
{
}

void System::KeyHandleSystem::operator()()
{
    for (auto it = _events.beginIterator<Event::Key>();
         it != _events.endIterator<Event::Key>(); it++) {
        if (it->key == KEY_SPACE) {
            auto &jumpCompList = _reg.get_components<Component::Jump>();
            for (auto it = jumpCompList.begin(); it != jumpCompList.end();
                 ++it) {
                if ((*it)->isJumping == false) {
                    (*it)->isJumping = true;
                    std::cout << "start jump" << std::endl;
                }
            }
        }
    }
}
