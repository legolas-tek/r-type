/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Position
*/

#include <cstddef>

#ifndef POSITION_HPP_
#define POSITION_HPP_

namespace Component
{
    struct Position
    {
        public:
            Position(float x = 0, float y = 0) : _x(x) , _y(y) {}
            float _x;
            float _y;
    };
}

#endif /* !POSITION_HPP_ */
