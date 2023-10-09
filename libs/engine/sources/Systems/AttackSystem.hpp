/*
** EPITECH PROJECT, 2023
** engine
** File description:
** AttackSystem
*/

#ifndef ATTACKSYSTEM_HPP_
#define ATTACKSYSTEM_HPP_

#include "ISystem.hpp"
#include "SparseArray.hpp"

#include "Components/AttackComponent.hpp"

/// @brief This system allows an entity to launch an attack if it has the attack
/// component set on true
namespace System {

class AttackSystem : public ISystem {
    public:
        AttackSystem(SparseArray<Component::AttackComponent> const &attacks) : _attacks(attacks) {}
        AttackSystem(System::AttackSystem const &other) = delete;
        void operator()() {
            // system logic
        }
    private:
        SparseArray<Component::AttackComponent> const &_attacks;
};
}

#endif /* !ATTACKSYSTEM_HPP_ */
