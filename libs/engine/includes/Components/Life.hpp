/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Life
*/

#ifndef LIFE_HPP_
#define LIFE_HPP_

#include "Serialization/Serializable.hpp"

namespace Component {

/// @brief This component allows our entity to have a life wich if it reaches 0
/// the lifeSystem will end the current game
struct Life : engine::Serializable<Life> {
    /// @brief Constructs an instance of a LifeTime component
    /// @param lifes The number of lifes the entity will have
    Life(int lifes) : lifes(lifes) {}

    /// @brief Default constructor
    Life() = default;

    /// @brief The number of lifes the entity has
    int lifes = 1;
};

}
#endif /* !LIFE_HPP_ */
