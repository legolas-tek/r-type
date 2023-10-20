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

#include "Serialization/Serializable.hpp"

namespace Component {

/**
 * @brief Structure representing a hitbox.
 *
 * This structure is used to represent a hitbox for collision detection.
 * It stores the position (x, y) and dimensions (width and height) of the
 * hitbox. It can be used as a component in a collision detection system.
 */
struct HitBox : engine::Serializable<HitBox> {
    /**
     * @brief Constructor for the HitBox structure.
     *
     * Initializes an instance of the HitBox structure with the specified
     * dimensions.
     *
     * @param width The width of the hitbox.
     * @param height The height of the hitbox.
     */
    HitBox(float width, float height)
        : _width(width)
        , _height(height)
    {
    }

    /**
     * @brief Default constructor for the HitBox structure.
     */
    HitBox() = default;

    /**
     * @brief The width of the hitbox.
     */
    float _width = 0;

    /**
     * @brief The height of the hitbox.
     */
    float _height = 0;
};
}

#endif /* !HITBOX_HPP_ */
