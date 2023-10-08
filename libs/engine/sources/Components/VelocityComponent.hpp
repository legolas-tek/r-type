/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** velocity
*/

#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

#include <cstddef>
#include <cstring>
#include <vector>

namespace Component {

/**
 * @brief Structure representing a velocity.
 *
 * This structure is used to represent a velocity with x and y components.
 * It can be used as a component to store the velocity of an entity.
 */
struct Velocity {
    /**
     * @brief The x-component of the velocity.
     */
    float _vx;

    /**
     * @brief The y-component of the velocity.
     */
    float _vy;

    /**
     * @brief Constructor for the Velocity structure.
     *
     * Initializes an instance of the Velocity structure with the specified x
     * and y components.
     *
     * @param vx The x-component of the velocity.
     * @param vy The y-component of the velocity.
     */
    Velocity(float vx = 0, float vy = 0)
        : _vx(vx)
        , _vy(vy)
    {
    }

    /**
     * @brief Serializes the Velocity structure into a byte vector.
     *
     * @return A vector containing the serialized bytes of the Velocity
     * structure.
     */
    std::vector<std::byte> serialize() const
    {
        std::vector<std::byte> vec(sizeof(Velocity));
        std::memcpy(vec.data(), this, sizeof(Velocity));
        return vec;
    }

    /**
     * @brief Deserializes a byte buffer into the Velocity structure.
     *
     * @param buffer A pointer to the byte buffer containing serialized Velocity
     * data.
     * @return The size of the serialized data that was deserialized
     * (sizeof(Velocity)).
     */
    size_t deserialize(std::byte const *buffer)
    {
        std::memcpy(this, buffer, sizeof(Velocity));
        return sizeof(Velocity);
    }
};

}
#endif /* !VELOCITY_HPP_ */
