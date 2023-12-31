/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Collision Component
*/

#ifndef COLLISION_HPP_
#define COLLISION_HPP_

#include <cstddef>
#include <optional>
#include <utility>

#include "Entity.hpp"
#include "Serialization/Serializable.hpp"
#include "Serialization/Serializer.hpp"

namespace Component {

/**
 * @brief Structure representing a collision.
 *
 * This structure is used to represent a box for collision detection in a
 * game or application. It stores the dimensions (width and height) of the
 * box. It can be used as a component in a collision detection system.
 */
struct Collision {
    /**
     * @brief Constructor for the collision structure.
     *
     * Initializes an instance of the collision structure with the specified
     * dimensions.
     *
     * @param width The width of the box.
     * @param height The height of the box.
     */
    Collision(float width, float height)
        : _width(width)
        , _height(height)
    {
    }

    /**
     * @brief Default constructor for the collision structure.
     */
    Collision() = default;

    /**
     * @brief The width of the collision.
     */
    float _width = 0;

    /**
     * @brief The height of the collision.
     */
    float _height = 0;

    void serialize(engine::Serializer &serializer) const
    {
        serializer.serializeTrivial(_width);
        serializer.serializeTrivial(_height);
    }

    void deserialize(engine::Deserializer &deserializer)
    {
        deserializer.deserializeTrivial(_width);
        deserializer.deserializeTrivial(_height);
    }
};
}

#endif /* !COLLISION_HPP_ */
