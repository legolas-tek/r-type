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
    Parallax(float startPosX, float startPosY)
        : _startPosX(startPosX)
        , _startPosY(startPosY)
    {
    }

    Parallax() = default;

    float _startPosX = 0.0f;
    float _startPosY = 0.0f;
};

}

#endif /* !PARALLAX_HPP_ */
