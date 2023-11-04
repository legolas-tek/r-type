/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Damage Handler System
*/

#include "Systems/DamageHandler.hpp"
#include "Events/Damage.hpp"

System::DamageHandler::DamageHandler(
    SparseArray<Component::Health> &healths, event::EventQueue &events
)
    : _healths(healths)
    , _events(events)
{
}

void System::DamageHandler::operator()()
{
    for (auto &damage : _events.getEvents<event::Damage>()) {

        if (not _healths[damage.entity])
            continue;

        _healths[damage.entity]->health -= damage.damages;
    }
}
