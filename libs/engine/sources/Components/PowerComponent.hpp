/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Power
*/

#ifndef POWER_HPP_
#define POWER_HPP_

#include <cstddef>

namespace Component {

/**
 * @brief Structure representing a power value.
 *
 * This structure is used to represent a power value associated with an entity.
 * It can be used as a component to store the power level of an entity.
 */
struct Power {
    /**
     * @brief Constructor for the Power structure.
     *
     * Initializes an instance of the Power structure with the specified power
     * value.
     *
     * @param power The power value associated with the entity.
     */
    Power(int power)
        : _power(power)
    {
    }

    /**
     * @brief The power value associated with the entity.
     */
    int _power;
};

}

#endif /* !POWER_HPP_ */