/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** HitBox
*/

#ifndef HITBOX_HPP_
    #define HITBOX_HPP_

#include <cstddef>
#include <utility>

namespace Component {

struct HitBox {
    HitBox(std::pair<int, int> pos, std::pair<int, int> size) : _pos(pos), _size(size) {}

    std::pair<int, int> _pos;
    std::pair<int, int> _size;
};

}

#endif /* !HITBOX_HPP_ */
