/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** JumpSystem
*/

#ifndef JUMPSYSTEM_HPP_
#define JUMPSYSTEM_HPP_

#include "ISystem.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"

#include "Components/Gravity.hpp"
#include "Components/Jump.hpp"
#include "Components/Velocity.hpp"

namespace System {

class JumpSystem : public ISystem {
public:
    JumpSystem(
        engine::Registry &reg, SparseArray<Component::Jump> &jump,
        SparseArray<Component::Gravity> &gravities,
        SparseArray<Component::Velocity> &velocities
    );
    // ~JumpSystem();

    void operator()() override;

protected:
private:
    bool isOnSolid(engine::Entity jumpentity);
    engine::Registry &_reg;
    SparseArray<Component::Jump> &_jumps;
    SparseArray<Component::Gravity> &_gravities;
    SparseArray<Component::Velocity> &_velocities;
};
}
#endif /* !JUMPSYSTEM_HPP_ */
