/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <cstddef>
#include <cstring>
#include <vector>

namespace Component {

struct Position {
    float _x = 0;
    float _y = 0;

    Position() = default;
    Position(float x, float y)
        : _x(x)
        , _y(y)
    {
    }

    std::vector<char> serialize() const
    {
        std::vector<char> vec(sizeof(Position));

        std::memcpy(vec.data(), this, sizeof(Position));
        return vec;
    }

    size_t deserialize(char const *buffer)
    {
        std::memcpy(this, buffer, sizeof(Position));
        return sizeof(Position);
    }
};

}

#endif /* !POSITION_HPP_ */
