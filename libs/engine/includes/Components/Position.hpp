/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Position Component
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <cstddef>
#include <cstring>
#include <vector>

#include <cstddef>

#include "Serializable.hpp"

namespace Component {

/**
 * @brief Structure representing a 2D position.
 *
 * This structure is used to represent a 2D position with x and y coordinates.
 * It can be used as a component to store the position of an entity.
 */
struct Position : Serializable<Position> {
    /**
     * @brief The x-coordinate of the position.
     */
    float _x = 0;

    /**
     * @brief The y-coordinate of the position.
     */
    float _y = 0;

    /**
     * @brief The z-coordinate of the position.
     */
    int _z = 0;

    /**
     * @brief Default constructor for the Position structure.
     *
     * Initializes an instance of the Position structure with default values (0,
     * 0).
     */
    Position() = default;

    /**
     * @brief Constructor for the Position structure with specified coordinates.
     *
     * Initializes an instance of the Position structure with the specified x
     * and y coordinates.
     *
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     * @param z The z-coordinate of the position.
     */
    Position(float x, float y, int z)
        : _x(x)
        , _y(y)
        , _z(z)
    {
    }
};

}

#endif /* !POSITION_HPP_ */
