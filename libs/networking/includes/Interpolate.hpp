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

#include "Components/Velocity.hpp"

namespace net {

/**
 * @brief Interpolation system abstract class.
 * This abstract contain the needed function to interpolate wanted variables
 * in the engine.
 */
class Interpolate : public ISystem {

public:
    Interpolate(SparseArray<Component::Velocity> &velocities);

    void operator()() override;

private:
    SparseArray<Component::Velocity> &_velocities;
};

}

#endif /* INTERPOLATE_HPP_ */
