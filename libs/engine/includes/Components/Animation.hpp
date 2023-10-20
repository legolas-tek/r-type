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
        float textureWidth, float textureHeight, float entityWidth,
        float entityHeight, float offset, size_t duration
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

    float _textureWidth = 0;
    float _textureHeight = 0;
    float _entityWidth = 0;
    float _entityHeight = 0;
    float _offset = 1; ///< The number of sprites in the animation.
    float _currentOffset = 0; ///< The current index of the animation.
    size_t _duration = 0;
};
}

#endif /* !ANIMATION_HPP_ */
