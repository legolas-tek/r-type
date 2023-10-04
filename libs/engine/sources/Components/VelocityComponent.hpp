/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** velocity
*/

#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

#include <cstddef>
#include <cstring>
#include <vector>

namespace Component {

struct Velocity {
    float _vx;
    float _vy;

    Velocity(float vx = 0, float vy = 0)
        : _vx(vx)
        , _vy(vy)
    {
    }

    std::vector<char> serialize() const
    {
        std::vector<char> vec(sizeof(Velocity));

        std::memcpy(vec.data(), this, sizeof(Velocity));
        return vec;
    }

    size_t deserialize(char const *buffer)
    {
        std::memcpy(this, buffer, sizeof(Velocity));
        return sizeof(Velocity);
    }
};

}
#endif /* !VELOCITY_HPP_ */
