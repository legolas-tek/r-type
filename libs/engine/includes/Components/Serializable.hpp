/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Component Serializer
*/

#ifndef R_TYPE_SERIALIZABLE_HPP
#define R_TYPE_SERIALIZABLE_HPP

#include <cstddef>
#include <cstring>
#include <vector>

template <typename T> struct Serializable {
    std::vector<std::byte> serialize() const
    {
        std::vector<std::byte> vec(sizeof(T));
        std::memcpy(vec.data(), this, sizeof(T));
        return vec;
    }

    size_t deserialize(std::byte const *buffer)
    {
        std::memcpy(this, buffer, sizeof(T));
        return sizeof(T);
    }
};

#endif // R_TYPE_SERIALIZABLE_HPP
