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
            position(int x = 0, int y = 0) : _x(x) , _y(y) {}
            int _x;
            int _y;
    };
}

#endif /* !POSITION_HPP_ */
