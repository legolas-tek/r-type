/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** velocity
*/

#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

namespace Component
{
    struct velocity
    {
        velocity(int vx = 0, int vy = 0) : _vx(vx) , _vy(vy) {}
        float _vx;
        float _vy;
    };
}
#endif /* !VELOCITY_HPP_ */
