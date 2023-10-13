/*
** EPITECH PROJECT, 2023
** engine
** File description:
** AttackSystem
*/

#ifndef ATTACKSYSTEM_HPP_
#define ATTACKSYSTEM_HPP_

#include "SparseArray.hpp"
#include "ISystem.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

#include "Components/Attack.hpp"

/// @brief This system checks wherever the entity is attacking with the attack
/// component. If it does it launches an attack creating an entity and set back
/// the attack component to true.
namespace System {

class AttackSystem : public ISystem {
public:
    AttackSystem(
        SparseArray<Component::Attack> &attacks,
        engine::Registry &reg
        );

    /// @brief deleted copy constructor
    AttackSystem(System::AttackSystem const &other) = delete;

    ~AttackSystem() = default;

    void operator()();
private:
    SparseArray<Component::Attack> &_attacks;
    engine::Registry &_register;
};
}

#endif /* !ATTACKSYSTEM_HPP_ */
