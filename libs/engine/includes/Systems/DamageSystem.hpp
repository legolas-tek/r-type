/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DamageSystem
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
class DamageSystem : public ISystem {

public:
    /// @brief constructs an instance of a DamageSystem class
    /// @param damages A ref to a Damage components SparseArray
    /// @param lifes A ref to a LifeTime components SparseArray
    /// @param collisions A ref to a Collision components SparseArray
    DamageSystem(
        SparseArray<Component::Damage> &damages,
        SparseArray<Component::Health> &healths, Event::EventQueue &event
    );

    /// @brief applies the logic of the system
    void operator()() override;

private:
    /// @brief A ref to a Damage components SparseArray
    SparseArray<Component::Damage> &_damages;
    /// @brief A ref to a LifeTime components SparseArray
    SparseArray<Component::Health> &_healths;
    /// @brief A ref to the EventQueue
    Event::EventQueue &_events;
};

}
#endif /* !DAMAGESYSTEM_HPP_ */
