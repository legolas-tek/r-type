/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Dependent
*/

#ifndef R_TYPE_DEPENDENT_HPP_
#define R_TYPE_DEPENDENT_HPP_

#include "Serialization/Serializable.hpp"
#include "Entity.hpp"

namespace Component {

/// @brief This component allows our entity to die whenever the entity it is
/// linked to dies
struct Dependent : engine::Serializable<Dependent> {
    /// @brief Constructs an instance of a Dependent component and sets the
    /// entity it owner depends on
    /// @param Dependents The entity the owner will depend on
    explicit Dependent(engine::Entity targetEntity)
        : targetEntity(targetEntity) {};

    /// @brief Default constructor
    Dependent() = default;

    /// @brief The Dependents the entity is dealing
    engine::Entity targetEntity = engine::Entity(1);
};

}
#endif /* !R_TYPE_DEPENDENT_HPP_ */
