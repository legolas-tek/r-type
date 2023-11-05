/*
** EPITECH PROJECT, 2023
** R-Type Engine
** File description:
** Events
*/

#include "Events/Close.hpp"
#include "Events/Collision.hpp"
#include "Events/Damage.hpp"
#include "Events/Death.hpp"
#include "Events/IEvent.hpp"
#include "Events/Mouse.hpp"

#include <ostream>

void event::IEvent::dump(std::ostream &stream) const
{
    stream << typeid(*this).name();
}

void event::Close::dump(std::ostream &stream) const
{
    stream << "Close";
}

void event::Collision::dump(std::ostream &stream) const
{
    stream << "Collision (" << entity << ", " << secondEntity << ")";
}

void event::Damage::dump(std::ostream &stream) const
{
    stream << "Damage (" << entity << ", " << damages << "hp)";
}

void event::Death::dump(std::ostream &stream) const
{
    stream << "Death (" << entity << ")";
}

void event::Mouse::dump(std::ostream &stream) const
{
    char const *names[] = { "RIGHT", "LEFT", "MIDDLE" };
    stream << "Mouse (" << names[int(type)] << " at " << x << ", " << y << ")";
}
