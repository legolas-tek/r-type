/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** HurtBox
*/

#ifndef HURTBOX_HPP_
#define HURTBOX_HPP_

#include <cstddef>
#include <utility>

namespace Component {

/**
 * @brief Structure representing a hurtbox.
 *
 * This structure is used to represent a hurtbox for collision detection in a
 * game or application. It stores the dimensions (width and height) of the
 * hurtbox. It can be used as a component in a collision detection system.
 */
struct HurtBox {
    /**
     * @brief Constructor for the HurtBox structure.
     *
     * Initializes an instance of the HurtBox structure with the specified
     * dimensions.
     *
     * @param width The width of the hurtbox.
     * @param height The height of the hurtbox.
     */
    HurtBox(float width, float height)
        : _width(width)
        , _height(height)
    {
    }

    /**
     * @brief The width of the hurtbox.
     */
    float _width;

    /**
     * @brief The height of the hurtbox.
     */
    float _height;
};

}

#endif /* !HURTBOX_HPP_ */
