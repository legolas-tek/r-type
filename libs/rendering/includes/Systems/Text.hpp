/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Text
*/

#ifndef R_TYPE_TEXT_HPP
#define R_TYPE_TEXT_HPP

#include "Components/Position.hpp"
#include "Components/Text.hpp"
#include "ISystem.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"
#include "raylib.h"

namespace rendering::system {

struct Text : public ISystem {
    Text(
        SparseArray<Component::Text> &texts,
        SparseArray<Component::Position> &positions
    );
    ~Text() override;
    void operator()() override;

private:
    bool isFontLoaded(std::string const &path);
    SparseArray<Component::Text> &_texts;
    SparseArray<Component::Position> &_positions;
    std::unordered_map<std::string, Font> _cache;
};

}

#endif // R_TYPE_TEXT_HPP
