/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Position Component
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <cstddef>
#include <cstring>
#include <vector>

#include <cstddef>

#include "Serialization/Serializable.hpp"

namespace Component {

/**
 * @brief Structure representing a 2D position.
 *
 * This structure is used to represent a 2D position with x and y coordinates.
 * It can be used as a component to store the position of an entity.
 */
struct Position {
    /**
     * @brief The x-coordinate of the position.
     */
    float _x = 0;

    /**
     * @brief The y-coordinate of the position.
     */
    float _y = 0;

    /**
     * @brief The z-coordinate of the position.
     */
    float _z = 0;

    /**
     * @brief The future x-coordinate of the position.
     */
    float _futureX = 0;

    /**
     * @brief The future y-coordinate of the position.
     */
    float _futureY = 0;

    /**
     * @brief The future z-coordinate of the position.
     */
    float _futureZ = 0;

    /**
     * @brief Default constructor for the Position structure.
     *
     * Initializes an instance of the Position structure with default values (0,
     * 0).
     */
    Position() = default;

    /**
     * @brief Constructor for the Position structure with specified coordinates.
     *
     * Initializes an instance of the Position structure with the specified x
     * and y coordinates.
     *
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     * @param z The z-coordinate of the position.
     */
    Position(float x, float y, float z = 0)
        : _x(x)
        , _y(y)
        , _z(z)
    {
    }

    void serialize(engine::Serializer &ser) const
    {
        ser.serializeTrivial<float>(_x);
        ser.serializeTrivial<float>(_y);
        ser.serializeTrivial<float>(_z);
    }

    void deserialize(engine::Deserializer &deser)
    {
        std::swap(_x, _futureX);
        std::swap(_y, _futureY);
        std::swap(_z, _futureZ);

        deser.deserializeTrivial<float>(_futureX);
        deser.deserializeTrivial<float>(_futureY);
        deser.deserializeTrivial<float>(_futureZ);
    }
};
}

#endif /* !POSITION_HPP_ */
