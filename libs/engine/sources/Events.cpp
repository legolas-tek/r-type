/*
** EPITECH PROJECT, 2023
** R-Type Engine
** File description:
** Events
*/

#include "Events/IEvent.hpp"

#include <ostream>

void event::IEvent::dump(std::ostream &stream) const
{
    stream << typeid(*this).name();
}
