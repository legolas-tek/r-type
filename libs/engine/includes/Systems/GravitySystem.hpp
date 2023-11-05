/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GravitySystem
*/

#ifndef GRAVITYSYSTEM_HPP_
#define GRAVITYSYSTEM_HPP_

#include "ISystem.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"

#include "Components/Gravity.hpp"
#include "Components/Velocity.hpp"

namespace System {

class GravitySystem : public ISystem {
public:
    GravitySystem(
        SparseArray<Component::Gravity> &gravities,
        SparseArray<Component::Velocity> &veocities
    );

    void operator()() override;

protected:
private:
    SparseArray<Component::Gravity> &_gravities;
    SparseArray<Component::Velocity> &_velocities;
};
}
#endif /* !GRAVITYSYSTEM_HPP_ */
