/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** HitBox
*/

#ifndef HITBOX_HPP_
#define HITBOX_HPP_

#include <cstddef>
#include <utility>

namespace Component {

struct HitBox {
    HitBox(float x, float y, float width, float height)
        : _x(x)
        , _y(y)
        , _width(width)
        , _height(height)
    {
    }

    float _x;
    float _y;
    float _width;
    float _height;
};

}

#endif /* !HITBOX_HPP_ */
