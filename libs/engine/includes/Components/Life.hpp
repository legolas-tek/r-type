/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Life Component
*/

#ifndef LIFE_HPP_
#define LIFE_HPP_

#include <cstddef>

#include "Serializable.hpp"

namespace Component {

/**
 * @brief Structure representing an entity's life.
 *
 * This structure is used to represent an entity's life and stores its unique
 * identifier and life value. It can be used as a component in a system for
 * managing the life of entities.
 */
struct Life : Serializable<Life> {
    /**
     * @brief Constructor for the Life structure.
     *
     * Initializes an instance of the Life structure with the specified
     * identifier and life value.
     *
     * @param id The unique identifier for the entity.
     * @param life The life value of the entity.
     */
    Life(int life)
        : _life(life)
    {
    }

    /**
     * @brief Default constructor for the Life structure.
     */
    Life() = default;

    /**
     * @brief The life value of the entity.
     */
    int _life = 0;
};

}

#endif /* !LIFE_HPP_ */
