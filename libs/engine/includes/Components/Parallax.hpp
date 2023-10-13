/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Parallax Component
*/

#ifndef PARALLAX_HPP_
#define PARALLAX_HPP_

#include <cstddef>
#include <utility>

#include "Entity.hpp"
#include "Serializable.hpp"

namespace Component {

/**
 * @brief Structure representing a parallax effect for an entity.
 *
 * The Parallax structure is used to create a parallax effect for an entity
 * within the game. It stores the starting position (X and Y coordinates) of
 * the entity, which will be used as a reference for the parallax effect.
 */
struct Parallax : Serializable<Parallax> {
public:
    /**
     * @brief Constructor for the Parallax structure.
     *
     * Initializes an instance of the Parallax structure with the specified
     * starting X and Y coordinates.
     *
     * @param startPosX The starting X coordinate for the parallax effect.
     * @param startPosY The starting Y coordinate for the parallax effect.
     */
    Parallax(float startPosX, float startPosY)
        : _startPosX(startPosX)
        , _startPosY(startPosY)
    {
    }

    /**
     * @brief Default constructor for the Parallax structure.
     */
    Parallax() = default;

    float _startPosX
        = 0.0f; ///< The starting X coordinate for the parallax effect.
    float _startPosY
        = 0.0f; ///< The starting Y coordinate for the parallax effect.
};

}

#endif /* !PARALLAX_HPP_ */
