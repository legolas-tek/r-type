/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Follow Component
*/

#ifndef R_TYPE_ENGINE_COMPONENTS_FOLLOW_HPP_
#define R_TYPE_ENGINE_COMPONENTS_FOLLOW_HPP_

#include "Entity.hpp"
#include "Serialization/Serializable.hpp"

namespace Component {

/// @brief This component allows an entity to follow another entity
struct Follow : engine::Serializable<Follow> {
    /// @brief Constrcust an instance of a Follow component and sets the
    /// followed entity
    /// @param followedEntity The entity wich the owner should follow
    /// @param offsetX The distance between the position of the followed entity
    /// and the position of the owner on the X axis
    /// @param offsetY The distance between the position of the followed entity
    /// and the position of the owner on the Y axis
    Follow(engine::Entity targetEntity, float offsetX, float offsetY)
        : targetEntity(targetEntity)
        , offsetX(offsetX)
        , offsetY(offsetY)
    {
    }

    /// @brief default constructor
    Follow() = default;

    /// @brief The entity the owner follow
    engine::Entity targetEntity = engine::Entity(0);
    /// @brief The X offset between the followed entity and the owner
    float offsetX = 0;
    /// @brief The Y offset between the followed entity and the owner
    float offsetY = 0;
};

}
#endif /* !R_TYPE_ENGINE_COMPONENTS_FOLLOW_HPP_ */
