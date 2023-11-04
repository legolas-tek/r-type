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

namespace System {

class JumpSystem : public ISystem {
public:
    JumpSystem(
        engine::Registry &reg, SparseArray<Component::Jump> &jump,
        SparseArray<Component::Gravity> &gravities
    );
    // ~JumpSystem();

    void operator()() override;

protected:
private:
    engine::Registry &_reg;
    SparseArray<Component::Jump> &_jumps;
    SparseArray<Component::Gravity> &_gravities;
};
}
#endif /* !JUMPSYSTEM_HPP_ */
