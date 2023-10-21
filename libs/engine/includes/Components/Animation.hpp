/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Animation Component
*/

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <cstddef>
#include <utility>

#include "Entity.hpp"
#include "Serialization/Serializable.hpp"

namespace Component {

/**
 * @brief The Animation struct represents an animation component for entities.
 */
struct Animation : engine::Serializable<Animation> {
public:
    /**
     * @brief Constructor to initialize the Animation component with the given
     * sprite number.
     *
     * @param offset The number of sprites in the animation.
     */
    Animation(
        size_t textureWidth, size_t textureHeight, float entityWidth,
        float entityHeight, size_t offset, size_t duration
    )
        : _textureWidth(textureWidth)
        , _textureHeight(textureHeight)
        , _entityWidth(entityWidth)
        , _entityHeight(entityHeight)
        , _offset(offset)
        , _duration(duration)
    {
    }

    /**
     * @brief Default constructor for the Animation component.
     */
    Animation() = default;

    size_t _textureWidth = 0;
    size_t _textureHeight = 0;
    float _entityWidth = 0;
    float _entityHeight = 0;
    size_t _offset = 1; ///< The number of sprites in the animation.
    size_t _currentOffset = 0; ///< The current index of the animation.
    size_t _duration = 0;
};
}

#endif /* !ANIMATION_HPP_ */
