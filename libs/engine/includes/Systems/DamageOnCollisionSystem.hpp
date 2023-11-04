/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DamageOnCollisionSystem
*/

#ifndef DAMAGESYSTEM_HPP_
#define DAMAGESYSTEM_HPP_

#include "ISystem.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"

#include "Components/Collision.hpp"
#include "Components/Damage.hpp"
#include "Components/Health.hpp"

namespace System {

/// @brief This system allows entity with the component damage to deal damage
/// on collision to entitys with the component life
class DamageOnCollisionSystem : public ISystem {

public:
    /// @brief constructs an instance of a DamageOnCollisionSystem class
    /// @param damages A ref to a Damage components SparseArray
    /// @param lifes A ref to a LifeTime components SparseArray
    /// @param collisions A ref to a Collision components SparseArray
    DamageOnCollisionSystem(
        SparseArray<Component::Damage> &damages,
        SparseArray<Component::Health> &healths, event::EventQueue &event
    );

    /// @brief applies the logic of the system
    void operator()() override;

private:
    /// @brief A ref to a Damage components SparseArray
    SparseArray<Component::Damage> &_damages;
    /// @brief A ref to a LifeTime components SparseArray
    SparseArray<Component::Health> &_healths;
    /// @brief A ref to the EventQueue
    event::EventQueue &_events;
};

}
#endif /* !DAMAGESYSTEM_HPP_ */
