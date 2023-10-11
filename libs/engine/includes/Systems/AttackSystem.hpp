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
#include "Components/HitBox.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

/// @brief This system checks wherever the entity is attacking with the attack
/// component. If it does it launches an attack creating an entity and set back
/// the attack component to true.
namespace System {

class AttackSystem : public ISystem {
public:
    AttackSystem(
        SparseArray<Component::Attack> &attacks,
        engine::Registry &reg
        ) : _attacks(attacks), _register(reg) {}

    /// @brief deleted copy constructor
    AttackSystem(System::AttackSystem const &other) = delete;

    ~AttackSystem() = default;

    void operator()() {
        for (auto &attack_comp : _attacks) {
            if (attack_comp.is_attacking) {
                engine::Entity attack(_register.get_new_entity());

                // _register.get_components<Component::HitBox>().emplace_at(attack, )
            }
        }
    }
private:
    SparseArray<Component::Attack> &_attacks;
    engine::Registry &_register;
};
}

#endif /* !ATTACKSYSTEM_HPP_ */
