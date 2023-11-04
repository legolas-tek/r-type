/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Editable System
*/

#ifndef R_TYPE_CLOSE_SYSTEM_HPP
#define R_TYPE_CLOSE_SYSTEM_HPP

#include "Events/Close.hpp"
#include "Events/EventQueue.hpp"

#include "ISystem.hpp"

namespace rendering::system {

struct Close : public ISystem {
    explicit Close(Event::EventQueue &events);
    void operator()() override;

private:
    Event::EventQueue &_events;
};

}

#endif // R_TYPE_CLOSE_SYSTEM_HPP
