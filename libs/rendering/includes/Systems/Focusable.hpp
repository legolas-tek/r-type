/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Focusable System
*/

#ifndef R_TYPE_FOCUSABLE_SYSTEM_HPP
#define R_TYPE_FOCUSABLE_SYSTEM_HPP

#include "Components/Focusable.hpp"
#include "Components/HitBox.hpp"
#include "Components/Position.hpp"
#include "ISystem.hpp"
#include "SparseArray.hpp"

namespace rendering::system {

/// @brief A system for handling focusable components in the R-Type game.
struct Focusable : public ISystem {
    /// @brief Constructor for the Focusable system.
    /// @param focusables A reference to the focusables component storage.
    /// @param hitboxes A reference to the hitboxes component storage.
    /// @param positions A reference to the positions component storage.
    Focusable(
        SparseArray<Component::Focusable> &focusables,
        SparseArray<Component::HitBox> &hitboxes,
        SparseArray<Component::Position> &positions
    );

    /// @brief Destructor for the Focusable system.
    ~Focusable() override;

    /// @brief Operator to execute the Focusable system.
    void operator()() override;

private:
    SparseArray<Component::Focusable> &_focusables;
    SparseArray<Component::HitBox> &_hitboxes;
    SparseArray<Component::Position> &_positions;
};

} // namespace rendering::system

#endif // R_TYPE_FOCUSABLE_SYSTEM_HPP
