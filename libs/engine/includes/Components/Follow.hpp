/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Follow Component
*/

#ifndef FOLLOW_HPP_
#define FOLLOW_HPP_

#include "Serialization/Serializable.hpp"
#include "Entity.hpp"

namespace Component {

/// @brief This component allows an entity to follow another entity
struct Follow : engine::Serializable<Follow> {
    /// @brief Constrcust an instance of a Follow component and sets the
    /// followed entity
    /// @param followedEntity The entity wich the owner should follow
    explicit Follow(
        engine::Entity targetEntity, float offsetX, float offsetY, float offsetZ
        )
        : targetEntity(targetEntity)
        , offsetX(offsetX)
        , offsetY(offsetY)
        , offsetZ(offsetZ)
    {
    }

    /// @brief default constructor
    Follow() = default;

    /// @brief The entity the owner follow
    engine::Entity targetEntity = engine::Entity(1);
    /// @brief The X offset between the followed entity and the owner
    float offsetX = 0;
    /// @brief The Y offset between the followed entity and the owner
    float offsetY = 0;
    /// @brief The Z offset between the followed entity and the owner
    float offsetZ = 0;
};

}
#endif /* !FOLLOW_HPP_ */
