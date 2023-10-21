/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Editable Component
*/

#ifndef R_TYPE_EDITABLE_HPP
#define R_TYPE_EDITABLE_HPP

#include "Serialization/Serializable.hpp"

namespace Component {

struct Editable : engine::Serializable<Editable> {
    Editable() = default;
    ~Editable() = default;
};

}

#endif // R_TYPE_EDITABLE_HPP
