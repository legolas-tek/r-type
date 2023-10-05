/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Life
*/

#ifndef LIFE_HPP_
    #define LIFE_HPP_

#include <cstddef>

namespace Component {

struct Life {
    Life(int id, int life) : _id(id), _life(life) {}

    int _id;
    int _life;
};

}

#endif /* !LIFE_HPP_ */
