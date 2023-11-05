/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** End System
*/

#include "End.hpp"
#include "Events/Death.hpp"
#include "Events/FinalBoss.hpp"

System::End::End(
    event::EventQueue &events,
    SparseArray<Component::Controllable> &controllables
)
    : _events(events)
    , _controllables(controllables)
{
}

bool System::End::hasControllables()
{
    for (auto &controllable : _controllables) {
        if (controllable)
            return true;
    }
    return false;
}

bool System::End::isDefeat()
{
    if (not hasControllables())
        _cooldown--;
    else
        _cooldown = _defaultCooldown;

    return _cooldown <= 0;
}

bool System::End::finalBossDied()
{
    for (auto &death : _events.getEvents<event::Death>()) {
        if (death.entity == _finalBoss)
            return true;
    }
    return false;
}

void System::End::operator()()
{
    if (not _finalBossSpawned) {
        for (auto &finalBoss : _events.getEvents<event::FinalBoss>()) {
            _finalBoss = finalBoss.entity;
            _finalBossSpawned = true;
        }
    }
    if (isDefeat()) {
        _events.addEvent<event::EndGame>(false);
    }
    if (_finalBossSpawned and finalBossDied()) {
        _events.addEvent<event::EndGame>(true);
    }
}
