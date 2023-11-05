/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** FloatingSystem
*/

#ifndef R_TYPE_FLOATINGSYSTEM_HPP_
#define R_TYPE_FLOATINGSYSTEM_HPP_

#include "ISystem.hpp"
#include "SparseArray.hpp"

#include "Components/Floating.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

namespace System {

/// @brief This system allows entities with the component Floating to move up
/// and down
class FloatingSystem : public ISystem {

public:
    /// @brief constructs an instance of a FloatingSystem class
    /// @param positions A ref to a Position components SparseArray
    /// @param velocities A ref to a Velocity components SparseArray
    /// @param floatings A ref to a Floating components SparseArray
    FloatingSystem(
        SparseArray<Component::Position> &positions,
        SparseArray<Component::Velocity> &velocities,
        SparseArray<Component::Floating> &floatings
    );

    /// @brief applies the logic of the system
    void operator()() override;

private:
    /// @brief Private method that change the velocity of an entity depending on
    /// it's Floating and Position Components values
    void adaptVelocity(
        Component::Position &position, Component::Velocity &velocity,
        Component::Floating &floating
    );

    /// @brief A ref to a Position components SparseArray
    SparseArray<Component::Position> &_positions;
    /// @brief A ref to a Velocity components SparseArray
    SparseArray<Component::Velocity> &_velocities;
    /// @brief A ref to a Floating components SparseArray
    SparseArray<Component::Floating> &_floatings;
};

}
#endif /* !R_TYPE_FLOATINGSYSTEM_HPP_ */
