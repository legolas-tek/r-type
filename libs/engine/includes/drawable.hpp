/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include "Sfml_SpriteFactory.hpp"

namespace Component {
struct drawable {
    drawable(Sprite &&sprite, bool drawable = true)
        : _is_drawable(drawable)
        , _sprite(sprite)
    {
    }
    bool _is_drawable;
    Sprite _sprite;
};
}

#endif /* !DRAWABLE_HPP_ */
