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

struct Parallax : Serializable<Parallax> {
    Parallax(float startPosX, float startPosY, size_t width, size_t height)
        : _startPosX(startPosX)
        , _startPosY(startPosY)
        , _width(width)
        , _height(height)
    {
    }

    Parallax() = default;

    float _startPosX = 0.0f;
    float _startPosY = 0.0f;
    size_t _width = 0;
    size_t _height = 0;
};

}

#endif /* !PARALLAX_HPP_ */
