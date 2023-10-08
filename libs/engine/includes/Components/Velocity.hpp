/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Velocity Component
*/

#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

#include <cstddef>
#include <cstring>
#include <vector>

namespace Component {

/**
 * @brief Structure representing a velocity.
 *
 * This structure is used to represent a velocity with x and y components.
 * It can be used as a component to store the velocity of an entity.
 */
struct Velocity : Serializable<Velocity> {
    /**
     * @brief The x-component of the velocity.
     */
    float _vx = 0;

    /**
     * @brief The y-component of the velocity.
     */
    float _vy = 0;

    /**
     * @brief Default constructor for the Velocity structure.
     *
     */
    Velocity() = default;

    /**
     * @brief Constructor for the Velocity structure.
     *
     * Initializes an instance of the Velocity structure with the specified x
     * and y components.
     *
     * @param vx The x-component of the velocity.
     * @param vy The y-component of the velocity.
     */
    Velocity(float vx, float vy)
        : _vx(vx)
        , _vy(vy)
    {
    }
};

}
#endif /* !VELOCITY_HPP_ */
