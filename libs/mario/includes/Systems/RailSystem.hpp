/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** RailSystem
*/

#ifndef RAILBACKGROUNDSYSTEM_HPP_
#define RAILBACKGROUNDSYSTEM_HPP_

#include "ISystem.hpp"

#include "SparseArray.hpp"

#include "Components/Rail.hpp"
#include "Components/Velocity.hpp"

namespace System {
class RailSystem : public ISystem {
public:
    RailSystem(
        SparseArray<Component::Rail> &rails,
        SparseArray<Component::Velocity> &velocities
    );

    void operator()() override;

protected:
private:
    SparseArray<Component::Rail> &_rails;
    SparseArray<Component::Velocity> &_velocities;
};
}

#endif /* !RAILBACKGROUNDSYSTEM_HPP_ */
