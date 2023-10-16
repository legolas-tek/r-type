/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Text Component
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "Serializable.hpp"
#include <string>
#include <utility>

namespace Component {

struct Text : Serializable<Text> {
    std::string _text;

    Text() = default;

    explicit Text(std::string text)
        : _text(std::move(text))
    {
    }
};

}

#endif
