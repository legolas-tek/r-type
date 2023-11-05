/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DeathOnCollisions
*/

#ifndef DEATHONCOLLISIONS_HPP_
#define DEATHONCOLLISIONS_HPP_

#include "ISystem.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"

#include "Components/Solid.hpp"
#include "Components/KillOnCollision.hpp"

namespace System {

/// @brief This system allows entity with the component KillOnCollision to die
/// whenever they collide with a solid entity
class DeathOnCollisions : public ISystem {

public:
    /// @brief constructs an instance of a DeathOnCollisions class
    /// @param solids A ref to a Solid components SparseArray
    /// @param killOnCollisions A ref to a KillOnCollision
    /// components SparseArray
    DeathOnCollisions(
        SparseArray<Component::Solid> &solids,
        SparseArray<Component::KillOnCollision> &killOnCollisions,
        event::EventQueue &events
    );

    /// @brief applies the logic of the system
    void operator()() override;

private:
    /// @brief checks whether an entity has already a death event raised or not
    /// @param entity the entity it checks
    /// @return returns true if the entity already ahs a death event and false
    /// if it doesn't
    bool isAlreadyInDeathEvent(engine::Entity entity) const;

    /// @brief A ref to a Solid components SparseArray
    SparseArray<Component::Solid> &_solids;
    /// @brief A ref to a KillOnCollision components SparseArray
    SparseArray<Component::KillOnCollision> &_killOnCollisions;
    /// @brief A ref to the EventQueue
    event::EventQueue &_events;
};

}

#endif /* !DEATHONCOLLISIONS_HPP_ */
