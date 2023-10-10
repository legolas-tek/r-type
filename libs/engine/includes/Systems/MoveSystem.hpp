/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Move System
*/

#ifndef MOVE_SYSTEM_HPP_
#define MOVE_SYSTEM_HPP_

#include "ISystem.hpp"
#include "SparseArray.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

namespace System {
class MoveSystem : public ISystem {
public:
    MoveSystem(
        SparseArray<Component::Position> &positions,
        SparseArray<Component::Velocity> &velocities
    );

    void operator()() override;

private:
    SparseArray<Component::Position> &_positions;
    SparseArray<Component::Velocity> &_velocities;
};
}

#endif /* !MOVE_SYSTEM_HPP_ */
