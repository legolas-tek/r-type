/*
** EPITECH PROJECT, 2023
** R-Type Engine
** File description:
** Events
*/

#include "Events/KeyDown.hpp"
#include "Events/KeyPressed.hpp"

#include <ostream>

void event::KeyPressed::dump(std::ostream &stream) const
{
    stream << "KeyPressed (" << entity << ", " << key << ")";
}

void event::KeyDown::dump(std::ostream &stream) const
{
    stream << "KeyDown (" << entity << ", " << key << ")";
}
