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
    Drawable(std::string path) : _path(std::move(path)) {}

    std::string _path;
};

}

#endif /* !Drawable_HPP_ */
