/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Follow Component
*/

#ifndef R_TYPE_ENGINE_COMPONENTS_SOLID_HPP_
#define R_TYPE_ENGINE_COMPONENTS_SOLID_HPP_

#include "Serialization/Serializable.hpp"
#include "Entity.hpp"

namespace Component {

/// @brief This component allows an entity to be solid and deny other entities
/// to pass through it
struct Solid : engine::Serializable<Solid> {
    /// @brief default constructor
    Solid() = default;
};

}
#endif /* !R_TYPE_ENGINE_COMPONENTS_SOLID_HPP_ */
