/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Loots
*/

#ifndef R_TYPE_LOOTS_HPP_
#define R_TYPE_LOOTS_HPP_

#include "Serialization/Serializable.hpp"

namespace Component {

/// @brief This component allows our entity to have a percentage of chances to
/// drop a bonus when killed
struct Loot : engine::Serializable<Loot> {
    /// @brief Default constructor
    Loot() = default;
};

}
#endif /* !R_TYPE_LOOTS_HPP_ */
