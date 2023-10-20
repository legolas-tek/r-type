/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Controllable Component
*/

#ifndef CONTROLLABLE_HPP_
#define CONTROLLABLE_HPP_

#include "Serialization/Serializable.hpp"

namespace Component {

/**
 * @brief Structure representing a controllable entity.
 *
 * This structure is used to represent a controllable entity and stores its
 * unique identifier. It can be used as a component in a system for managing
 * controllable entities.
 */
struct Controllable : engine::Serializable<Controllable> {
    /**
     * @brief Constructor for the Controllable structure.
     *
     * Initializes an instance of the Controllable structure with the specified
     * identifier.
     *
     * @param id The unique identifier for the controllable entity.
     */
    Controllable(int id)
        : _id(id)
    {
    }

    /**
     * @brief Default constructor for the Controllable structure.
     */
    Controllable() = default;

    /**
     * @brief The unique identifier for the controllable entity.
     */
    int _id = 0;
};
}

#endif /* !CONTROLLABLE_HPP_ */
