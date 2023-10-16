/*
** EPITECH PROJECT, 2023
** engine
** File description:
** AttackSystem
*/

#ifndef ATTACKSYSTEM_HPP_
#define ATTACKSYSTEM_HPP_

#include "Entity.hpp"
#include "ISystem.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"

#include "Components/Attack.hpp"

/// @brief change this value to change the index in wich the drawable component
/// will init the graphical object

/// @brief This system checks wherever the entity is attacking with the attack
/// component. If it does it launches an attack creating an entity and set back
/// the attack component to true.
namespace System {

class AttackSystem : public ISystem {
public:
    AttackSystem(
        SparseArray<Component::Attack> &attacks, engine::Registry &reg
    );

    /// @brief deleted copy constructor
    AttackSystem(System::AttackSystem const &other) = delete;

    ~AttackSystem() = default;

    void operator()() override;

private:
    /// @brief private function that create a laser
    /// @param attack_comp the attack component of the attacking entity
    /// @param attacker_index the index of the attacking entity
    void createLaserEntity(
        Component::Attack &attack_comp, engine::Entity const attacker_index
    );

    SparseArray<Component::Attack> &_attacks;
    engine::Registry &_register;
};
}

#endif /* !ATTACKSYSTEM_HPP_ */
