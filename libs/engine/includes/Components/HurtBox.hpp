/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** HurtBox Component
*/

#ifndef HURTBOX_HPP_
#define HURTBOX_HPP_

#include <cstddef>
#include <utility>

#include "Serializable.hpp"

namespace Component {

/**
 * @brief Structure representing a hurtbox.
 *
 * This structure is used to represent a hurtbox for collision detection in a
 * game or application. It stores the dimensions (width and height) of the
 * hurtbox. It can be used as a component in a collision detection system.
 */
struct HurtBox : Serializable<HurtBox> {
    /**
     * @brief Constructor for the HurtBox structure.
     *
     * Initializes an instance of the HurtBox structure with the specified
     * dimensions.
     *
     * @param width The width of the hurtbox.
     * @param height The height of the hurtbox.
     */
    HurtBox(float x, float y, float width, float height, int damage)
        : _x(x)
        , _y(y)
        , _width(width)
        , _height(height)
        , _damage(damage) {};

    /**
     * @brief The x-coordinate of the top-left corner of the hurtbox.
     * Is a relative position to the entity's position.
     */
    float _x;

    /**
     * @brief The y-coordinate of the top-left corner of the hurtbox.
     * Is a relative position to the entity's position.
     */
    float _y;

    /**
     * @brief The width of the hurtbox.
     */
    float _width;

    /**
     * @brief The height of the hurtbox.
     */
    float _height;

    /**
     * @brief The damage of the hurtbox.
     */
    int _damage;
};

}

#endif /* !HURTBOX_HPP_ */
