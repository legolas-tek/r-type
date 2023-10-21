/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Focusable Component
*/

#ifndef R_TYPE_FOCUSABLE_HPP
#define R_TYPE_FOCUSABLE_HPP

#include "Serialization/Serializable.hpp"

namespace Component {
/// @brief This component allows our entity to be focusable
struct Focusable : engine::Serializable<Focusable> {
    /// @brief construct an instance of a Focusable component
    /// @param isFocused The focusable state of the entity
    explicit Focusable(bool isFocused)
        : isFocused(isFocused)
    {
    }

    /// @brief default constructor
    Focusable() = default;

    /// @brief The focusable state of the entity
    bool isFocused = false;
};
}

#endif // R_TYPE_FOCUSABLE_HPP
