/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Restart System
*/

#include "Systems/ScoreOnDeath.hpp"
#include "Components/ScoreOnDeath.hpp"
#include "Events/Death.hpp"
#include "ScoreManager.hpp"

System::ScoreOnDeath::ScoreOnDeath(
    event::EventQueue &events, ScoreManager &scoreManager,
    SparseArray<Component::ScoreOnDeath> &scoreOnDeaths
)
    : _events(events)
    , _scoreManager(scoreManager)
    , _scoreOnDeaths(scoreOnDeaths)
{
}

void System::ScoreOnDeath::operator()()
{
    for (auto it = _scoreOnDeaths.begin(); it != _scoreOnDeaths.end(); it++) {
        auto entity = it.get_entity();

        for (auto &death : _events.getEvents<event::Death>()) {
            if (death.entity == entity) {
                _scoreManager.addScore((*it)->score);
            }
        }
    }
}
