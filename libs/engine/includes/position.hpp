/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** position
*/

#include <cstddef>

#ifndef POSITION_HPP_
#define POSITION_HPP_

namespace Component
{
    struct position
    {
        public:
            position(float x = 0, float y = 0) : _x(x) , _y(y) {}
            float _x;
            float _y;
    };
}

#endif /* !POSITION_HPP_ */
