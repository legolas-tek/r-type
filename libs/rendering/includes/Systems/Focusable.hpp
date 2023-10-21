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

struct Focusable : public ISystem {
    Focusable(
        SparseArray<Component::Focusable> &focusables,
        SparseArray<Component::HitBox> &hitboxes,
        SparseArray<Component::Position> &positions
    );
    ~Focusable() override;
    void operator()() override;

private:
    SparseArray<Component::Focusable> &_focusables;
    SparseArray<Component::HitBox> &_hitboxes;
    SparseArray<Component::Position> &_positions;
};
}

#endif // R_TYPE_FOCUSABLE_SYSTEM_HPP
