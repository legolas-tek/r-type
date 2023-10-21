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
    /// @param isFocusable The focusable state of the entity
    explicit Focusable(bool isFocusable)
        : isFocusable(isFocusable)
    {
    }

    /// @brief default constructor
    Focusable() = default;

    /// @brief The focusable state of the entity
    bool isFocusable = false;
};
}

#endif // R_TYPE_FOCUSABLE_HPP
