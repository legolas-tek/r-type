/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Move System
*/

#ifndef MOVE_SYSTEM_HPP_
#define MOVE_SYSTEM_HPP_

#include "ISystem.hpp"
#include "Registry.hpp"

#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

namespace System {
struct MoveSystem : public ISystem {
    MoveSystem(
        SparseArray<Component::Position> &positions,
        SparseArray<Component::Velocity> &velocities
    );

    void operator()() override;

    SparseArray<Component::Position> &_positions;
    SparseArray<Component::Velocity> &_velocities;
};
}

#endif /* !MOVE_SYSTEM_HPP_ */
