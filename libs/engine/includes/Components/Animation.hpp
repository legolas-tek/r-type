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

struct Animation : Serializable<Animation> {
    Animation(size_t spriteNum)
        : _spriteNum(spriteNum)
    {
    }

    Animation() = default;

    size_t _spriteNum = 1;
    size_t _current_index = 0;

};

}

#endif /* !ANIMATION_HPP_ */
