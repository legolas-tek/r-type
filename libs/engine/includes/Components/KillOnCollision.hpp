/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** KillOnCollision
*/

#ifndef R_TYPE_KILLONCOLLISION_HPP_
#define R_TYPE_KILLONCOLLISION_HPP_

#include "Entity.hpp"
#include "Serialization/Serializable.hpp"

namespace Component {

/// @brief This component allows our entity to die whenever it collides another
/// entity with a health or a solid component
struct KillOnCollision : engine::Serializable<KillOnCollision> {
    /// @brief Default constructor
    KillOnCollision() = default;
};

}
#endif /* !R_TYPE_KILLONCOLLISION_HPP_ */
