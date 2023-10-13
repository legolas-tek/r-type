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
     * @param spriteNum The number of sprites in the animation.
     */
    Animation(size_t spriteNum)
        : _spriteNum(spriteNum)
    {
    }

    /**
     * @brief Default constructor for the Animation component.
     */
    Animation() = default;

    size_t _spriteNum = 1; ///< The number of sprites in the animation.
    size_t _current_index = 0; ///< The current index of the animation.
};

}

#endif /* !ANIMATION_HPP_ */
