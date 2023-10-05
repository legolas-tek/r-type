/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** HurtBox
*/

#ifndef HURTBOX_HPP_
    #define HURTBOX_HPP_

#include <cstddef>
#include <utility>

namespace Component {

struct HurtBox {
    HurtBox(int id, std::pair<int, int> pos, std::pair<int, int> size) : _id(id), _pos(pos), _size(size) {}

    int _id;
    std::pair<int, int> _pos;
    std::pair<int, int> _size;
};

}

#endif /* !HURTBOX_HPP_ */
