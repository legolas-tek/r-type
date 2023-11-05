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
    for (auto it = _controllables.begin(); it != _controllables.end(); it++) {
        if (it->has_value())
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
    if (isDefeat() && not _gameIsEnded) {
        _events.addEvent<event::EndGame>(false);
        _gameIsEnded = true;
    }
    if (_finalBossSpawned and finalBossDied() and not _gameIsEnded) {
        _events.addEvent<event::EndGame>(true);
        _gameIsEnded = true;
    }
}
