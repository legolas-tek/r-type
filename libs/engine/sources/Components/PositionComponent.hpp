/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <cstddef>
#include <cstring>
#include <vector>

#include <cstddef>

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
     */
    Position(float x, float y)
        : _x(x)
        , _y(y)
    {
    }

    /**
     * @brief Serializes the Position structure into a byte vector.
     *
     * @return A vector containing the serialized bytes of the Position
     * structure.
     */
    std::vector<std::byte> serialize() const
    {
        std::vector<std::byte> vec(sizeof(Position));
        std::memcpy(vec.data(), this, sizeof(Position));
        return vec;
    }

    /**
     * @brief Deserializes a byte buffer into the Position structure.
     *
     * @param buffer A pointer to the byte buffer containing serialized Position
     * data.
     * @return The size of the serialized data that was deserialized
     * (sizeof(Position)).
     */
    size_t deserialize(std::byte const *buffer)
    {
        std::memcpy(this, buffer, sizeof(Position));
        return sizeof(Position);
    }
};

}

#endif /* !POSITION_HPP_ */
