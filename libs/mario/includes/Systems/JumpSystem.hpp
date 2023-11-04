/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** JumpSystem
*/

#ifndef JUMPSYSTEM_HPP_
#define JUMPSYSTEM_HPP_

#include "Components/Jump.hpp"
#include "ISystem.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"

namespace System {

class JumpSystem : public ISystem {
public:
    JumpSystem(engine::Registry &reg, SparseArray<Component::Jump> &jump);
    // ~JumpSystem();

    void operator()() override;

protected:
private:
    engine::Registry &_reg;
    SparseArray<Component::Jump> &_jumps;
};
}
#endif /* !JUMPSYSTEM_HPP_ */
