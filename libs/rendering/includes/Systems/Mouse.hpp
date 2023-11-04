/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Mouse
*/

#ifndef R_TYPE_MOUSE_EVENT_DETECT_HPP
#define R_TYPE_MOUSE_EVENT_DETECT_HPP

#include "Events/EventQueue.hpp"
#include "ISystem.hpp"

namespace rendering::system {

struct Mouse : public ISystem {

    Mouse(Event::EventQueue &events);
    void operator()() override;

private:
    Event::EventQueue &_events;
};

}

#endif // R_TYPE_MOUSE_EVENT_DETECT_HPP
