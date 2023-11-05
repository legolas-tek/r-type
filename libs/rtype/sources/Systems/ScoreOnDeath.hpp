/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Score on Death system
*/

#ifndef R_TYPE_SYSTEM_SCORE_ON_DEATH_HPP_
#define R_TYPE_SYSTEM_SCORE_ON_DEATH_HPP_

#include "Components/ScoreOnDeath.hpp"
#include "Events/EventQueue.hpp"
#include "ISystem.hpp"
#include "ScoreManager.hpp"
#include "SparseArray.hpp"

namespace System {

class ScoreOnDeath : public ISystem {
public:
    ScoreOnDeath(
        event::EventQueue &events, ScoreManager &scoreManager,
        SparseArray<Component::ScoreOnDeath> &scoreOnDeaths
    );
    void operator()() override;

private:
    event::EventQueue &_events;
    ScoreManager &_scoreManager;
    SparseArray<Component::ScoreOnDeath> &_scoreOnDeaths;
};

}

#endif /* !SYSTEM_SCORE_ON_DEATH_HPP_ */
