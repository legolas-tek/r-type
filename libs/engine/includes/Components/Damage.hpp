/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Damage
*/

#ifndef DAMAGE_HPP_
#define DAMAGE_HPP_

#include "Serialization/Serializable.hpp"

namespace Component {

/// @brief This component allows our entity to deal damages on collision and
/// will be used by the damage system
struct Damage : engine::Serializable<Damage> {
    /// @brief Constructs an instance of a Damage component and sets it's damage
    /// @param damages The damages that the entity will deal on collision
    Damage(int damages)
        : damages(damages) {};

    /// @brief Default constructor
    Damage() = default;

    /// @brief The damages the entity is dealing
    int damages = 1;
};
}
#endif /* !DAMAGE_HPP_ */
