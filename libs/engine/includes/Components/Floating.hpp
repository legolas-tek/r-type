/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Floating
*/

#ifndef R_TYPE_FLOATING_HPP_
#define R_TYPE_FLOATING_HPP_

#include "Serialization/Serializable.hpp"

namespace Component {
/// @brief This component allows our entity to float up and down on the screen
struct Floating : engine::Serializable<Floating> {
    /// @brief Constructs an instance of a Floating Component
    /// @param maxY The maximum value the entity will reach on the Y axis
    /// @param maxX The maximum value the entity will reach on the X axis
    /// @param minY The minimum value the entity will reach on the Y axis
    /// @param minX The minimum value the entuty will reach on the X axis
    /// @param speed The speed at wich the entity will move
    explicit Floating(
        float maxY, float maxX, float minY, float minX, float speed = 1
    )
        : maxY(maxY)
        , maxX(maxX)
        , minY(minY)
        , minX(minX)
        , speed(speed)
    {
    }

    /// @brief default constructor
    Floating() = default;

    /// @brief The maximum value the entity will reach on the Y axis
    float maxY = 0;
    /// @brief The maximum value the entity will reach on the X axis
    float maxX = 0;
    /// @brief The minimum value the entity will reach on the Y axis
    float minY = 0;
    /// @brief The minimum value the entuty will reach on the X axis
    float minX = 0;
    /// @brief The speed at wich the entity will move
    float speed = 0;
};
}

#endif /* !R_TYPE_FLOATING_HPP_ */
