/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** velocity
*/

#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

namespace Component {
struct Velocity {
    Velocity(float vx = 0, float vy = 0)
        : _vx(vx)
        , _vy(vy)
    {
    }
    float _vx;
    float _vy;
};
}
#endif /* !VELOCITY_HPP_ */
