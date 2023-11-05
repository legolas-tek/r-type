/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Score on Death Component
*/

#ifndef R_TYPE_COMPONENT_SCORE_ON_DEATH_HPP_
#define R_TYPE_COMPONENT_SCORE_ON_DEATH_HPP_

#include "Serialization/Serializable.hpp"

namespace Component {

struct ScoreOnDeath : engine::Serializable<ScoreOnDeath> {
    explicit ScoreOnDeath(int score = 1)
        : score(score)
    {
    }

    int score = 1;
};

}

#endif /*! COMPONENT_SCORE_ON_DEATH_HPP_ */
