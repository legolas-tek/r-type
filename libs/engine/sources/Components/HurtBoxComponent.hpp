/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** HurtBox
*/

#ifndef HURTBOX_HPP_
    #define HURTBOX_HPP_

#include <cstddef>
#include <utility>

namespace Component {

struct HurtBox {
    HurtBox(float width, float height) : _width(width), _height(height) {}

    float _width;
    float _height;
};

}

#endif /* !HURTBOX_HPP_ */
