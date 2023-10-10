/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Collision Component
*/

#ifndef COLLISION_HPP_
#define COLLISION_HPP_

#include <cstddef>
#include <utility>

#include "Serializable.hpp"

namespace Component {

/**
 * @brief Structure representing a Collision.
 *
 * This structure is used to represent a Collision for collision detection in a
 * game or application. It stores the dimensions (width and height) of the
 * Collision. It can be used as a component in a collision detection system.
 */
struct Collision : Serializable<Collision> {
    /**
     * @brief Constructor for the Collision structure.
     *
     * Initializes an instance of the Collision structure with the specified
     * dimensions.
     *
     * @param width The width of the Collision.
     * @param height The height of the Collision.
     */
    Collision(float x, float y, float width, float height, int damage)
        : _x(x)
        , _y(y)
        , _width(width)
        , _height(height)
        , _damage(damage) {};

    /**
     * @brief Default constructor for the Collision structure.
     */
    Collision() = default;

    /**
     * @brief The x-coordinate of the top-left corner of the Collision.
     * Is a relative position to the entity's position.
     */
    float _x = 0;

    /**
     * @brief The y-coordinate of the top-left corner of the Collision.
     * Is a relative position to the entity's position.
     */
    float _y = 0;

    /**
     * @brief The width of the Collision.
     */
    float _width = 0;

    /**
     * @brief The height of the Collision.
     */
    float _height = 0;

    /**
     * @brief The damage of the Collision.
     */
    int _damage = 0;
};

}

#endif /* !COLLISION_HPP_ */
