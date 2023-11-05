/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Interpolation system
*/

#ifndef INTERPOLATE_HPP_
#define INTERPOLATE_HPP_

#include "ISystem.hpp"
#include "Net.hpp"
#include "SparseArray.hpp"

#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

namespace net {

/**
 * @brief Interpolation system abstract class.
 * This abstract contain the needed function to interpolate wanted variables
 * in the engine.
 */
class Interpolate : public ISystem {

public:
    Interpolate(
        SparseArray<Component::Velocity> &velocities,
        SparseArray<Component::Position> &positions
    );

    void operator()() override;

private:
    SparseArray<Component::Velocity> &_velocities;
    SparseArray<Component::Position> &_positions;
};

}

#endif /* INTERPOLATE_HPP_ */
