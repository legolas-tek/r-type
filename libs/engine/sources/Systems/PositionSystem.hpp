/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Position_systeme
*/

#ifndef POSITION_SYSTEME_HPP_
#define POSITION_SYSTEME_HPP_

#include "ISystem.hpp"
#include "SparseArray.hpp"

#include "Components/PositionComponent.hpp"
#include "Components/VelocityComponent.hpp"

namespace System {

class Position_system : public ISystem {
public:
    Position_system(
        SparseArray<Component::Position> const &positions,
        SparseArray<Component::Velocity> const &velocities
    )
        : _positions(positions)
        , _velocities(velocities) {}
    Position_system(System::Position_system const &other) = delete;
    void operator()()
    {
        // system logic
    }
private:
    SparseArray<Component::Position> const &_positions;
    SparseArray<Component::Velocity> const &_velocities;
};
}

#endif /* !POSITION_SYSTEME_HPP_ */
