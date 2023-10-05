/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Animation
*/

#ifndef ANIMATION_HPP_
    #define ANIMATION_HPP_

#include <cstddef>

namespace Component {

struct Animation {
    Animation(int id) : _id(id) {}

    int _id;
};

}

#endif /* !ANIMATION_HPP_ */
