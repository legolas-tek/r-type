/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Drawable
*/


#ifndef DRAWABLE_HPP_
    #define DRAWABLE_HPP_

#include <cstddef>
#include <string>
#include <utility>

namespace Component {

struct Drawable {
    Drawable(int id, std::string path) : _id(id), _path(std::move(path)) {}

    int _id;
    std::string _path;
};

}

#endif /* !Drawable_HPP_ */
