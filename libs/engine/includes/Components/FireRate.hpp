/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** FireRate
*/

#ifndef FIRERATE_HPP_
#define FIRERATE_HPP_

#include "Serializable.hpp"

namespace Component {

/// @brief This component allows our entity to have a firerate and specifies
/// that when they attack they shoot lasers
struct FireRate : Serializable<FireRate> {
    /// @brief construct an instance of a Firerate component
    /// @param reload_ticks The ticks required for the entity to shoot again
    /// @param actual_tick The actual tick from registry
    FireRate(int reload_ticks)
        : _reload_ticks(reload_ticks)
    {
    }

    /// @brief default constructor
    FireRate() = default;

    /// @brief The ticks required for the entity to shoot again
    int _reload_ticks;
};

}
#endif /* !FIRERATE_HPP_ */
