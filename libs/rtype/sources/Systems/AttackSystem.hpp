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

#include "Components/FireRate.hpp"
#include "Components/Health.hpp"
#include "Components/Position.hpp"

namespace System {

/// @brief This system checks wherever the entity is attacking with the attack
/// component. If it does it launches an attack creating an entity and set back
/// the attack component to true.
class AttackSystem : public ISystem {
public:
    /// @brief The width of the laser sprite
    static inline constexpr int LASER_WIDTH = 50;
    /// @brief The height of the laser component
    static inline constexpr int LASER_HEIGHT = 4;
    /// @brief The number of frames for the laser animation
    static inline constexpr int LASER_FRAMES = 4;
    /// @brief The index to find the laser sprite
    static inline constexpr int LASER_INDEX = 4;

public:
    AttackSystem(
        SparseArray<Component::FireRate> &fireRates,
        SparseArray<Component::Health> &_healths,
        SparseArray<Component::Position> &positions, engine::Registry &reg
    );

    /// @brief deleted copy constructor
    AttackSystem(System::AttackSystem const &other) = delete;

    ~AttackSystem() override = default;

    void operator()() override;

private:
    /// @brief private function that create a laser
    /// @param attack_comp the attack component of the attacking entity
    /// @param attacker_index the index of the attacking entity
    void createLaserEntity(engine::Entity attacker_index);

    /// @brief private function that allows the attack system to know when he
    /// can create a laser entity
    /// @param fire_rates optional fire rate component of the attacking entity
    /// @return returns true if the entity can shoot or false if it has to
    /// wait more
    bool isAbleToAttack(Component::FireRate &fire_rate);

    /// @brief A ref to a FireRate components SparseArray
    SparseArray<Component::FireRate> &_fireRates;
    /// @brief A ref to a Health components SparseArray
    SparseArray<Component::Health> &_healths;
    /// @brief A ref to a Position components SparseArray
    SparseArray<Component::Position> &_positions;
    /// @brief A ref to the registry
    engine::Registry &_register;
};
}

#endif /* !ATTACKSYSTEM_HPP_ */
