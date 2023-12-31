/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** FireRate
*/

#ifndef FIRERATE_HPP_
#define FIRERATE_HPP_

#include "Serialization/Serializable.hpp"

namespace Component {

/// @brief This component allows our entity to have a firerate and specifies
/// when they attack to shoot lasers
struct FireRate : engine::Serializable<FireRate> {
    /// @brief construct an instance of a Firerate component
    /// @param reload_ticks The ticks required for the entity to shoot again
    explicit FireRate(int reload_ticks)
        : reload_ticks(reload_ticks)
    {
    }

    /// @brief default constructor
    FireRate() = default;

    /// @brief The ticks required for the entity to shoot again
    int reload_ticks = 1;
};
}
#endif /* !FIRERATE_HPP_ */
