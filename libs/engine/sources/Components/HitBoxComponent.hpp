/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** HitBox Component
*/

#ifndef HITBOX_HPP_
#define HITBOX_HPP_

#include <cstddef>
#include <utility>

#include "Serializable.hpp"

namespace Component {

/**
 * @brief Structure representing a hitbox.
 *
 * This structure is used to represent a hitbox for collision detection.
 * It stores the position (x, y) and dimensions (width and height) of the
 * hitbox. It can be used as a component in a collision detection system.
 */
struct HitBox : Serializable<HitBox> {
    /**
     * @brief Constructor for the HitBox structure.
     *
     * Initializes an instance of the HitBox structure with the specified
     * position and dimensions.
     *
     * @param x The x-coordinate of the top-left corner of the hitbox.
     * @param y The y-coordinate of the top-left corner of the hitbox.
     * @param width The width of the hitbox.
     * @param height The height of the hitbox.
     */
    HitBox(float x, float y, float width, float height)
        : _x(x)
        , _y(y)
        , _width(width)
        , _height(height)
    {
    }

    /**
     * @brief The x-coordinate of the top-left corner of the hitbox.
     * Is a relative position to the entity's position.
     */
    float _x;

    /**
     * @brief The y-coordinate of the top-left corner of the hitbox.
     * Is a relative position to the entity's position.
     */
    float _y;

    /**
     * @brief The width of the hitbox.
     */
    float _width;

    /**
     * @brief The height of the hitbox.
     */
    float _height;
};

}

#endif /* !HITBOX_HPP_ */
