/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Damage Handler System
*/

#include "Systems/DamageHandler.hpp"
#include "Events/Damage.hpp"

System::DamageHandler::DamageHandler(
    SparseArray<Component::Health> &healths, Event::EventQueue &events
)
    : _healths(healths)
    , _events(events)
{
}

void System::DamageHandler::operator()()
{
    for (auto it = _events.beginIterator<Event::Damage>();
         it != _events.endIterator<Event::Damage>(); it++) {
        auto damage = it;

        if (not _healths[damage->entity])
            continue;

        _healths[damage->entity]->health -= damage->damages;
    }
}
