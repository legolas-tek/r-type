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
#include "Serializable.hpp"

namespace Component {

/**
 * @brief The Animation struct represents an animation component for entities.
 */
struct Animation : Serializable<Animation> {
public:
    /**
     * @brief Constructor to initialize the Animation component with the given
     * sprite number.
     *
     * @param offset The number of sprites in the animation.
     */
    Animation(
        size_t texture_width, size_t texture_height, size_t entity_width,
        size_t entity_height, size_t offset, size_t duration
    )
        : _texture_width(texture_width)
        , _texture_height(texture_height)
        , _entity_width(entity_width)
        , _entity_height(entity_height)
        , _offset(offset)
        , _duration(duration)
    {
    }

    /**
     * @brief Default constructor for the Animation component.
     */
    Animation() = default;

    size_t _texture_width = 0;
    size_t _texture_height = 0;
    size_t _entity_width = 0;
    size_t _entity_height = 0;
    size_t _offset = 1; ///< The number of sprites in the animation.
    size_t _current_offset = 0; ///< The current index of the animation.
    size_t _duration = 0;
};
}

#endif /* !ANIMATION_HPP_ */
