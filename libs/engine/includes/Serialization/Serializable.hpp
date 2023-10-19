/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Component Serializer
*/

#ifndef R_TYPE_SERIALIZABLE_HPP
#define R_TYPE_SERIALIZABLE_HPP

#include "Deserializer.hpp"
#include "Serializer.hpp"

#include <cstddef>
#include <cstring>
#include <vector>

namespace engine {

template <typename T> struct Serializable {
    void serialize(Serializer &ser) const
    {
        ser.serializeTrivial(*this);
    }

    void deserialize(Deserializer &deser)
    {
        deser.deserializeTrivial(*this);
    }
};

}

#endif // R_TYPE_SERIALIZABLE_HPP
