/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AI Component
*/

#ifndef AI_HPP_
#define AI_HPP_

#include <cstddef>
#include <utility>

#include "Entity.hpp"
#include "Serializable.hpp"

namespace Component {

/**
 * @brief The AI struct represents an animation component for entities.
 */

enum AIType {
    SHOOT,
    SUICIDE_BOMING,
};

struct AI : Serializable<AI> {
public:
    /**
     * @brief Constructor to initialize the AI component with the given
     * sprite number.
     *
     * @param offset The number of sprites in the animation.
     */
    AI(AIType aiType)
        : _aiType(aiType)
    {
    }

    /**
     * @brief Default constructor for the AI component.
     */
    AI() = default;

    AIType _aiType = SHOOT;
};
}

#endif /* !AI_HPP_ */
