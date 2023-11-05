/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Move System
*/

#ifndef MOVE_SYSTEM_HPP_
#define MOVE_SYSTEM_HPP_

#include <memory>
#include <deque>

#include "Events/IEvent.hpp"
#include "Events/EventQueue.hpp"

#include "Components/Collision.hpp"
#include "Components/Position.hpp"
#include "Components/Solid.hpp"
#include "Components/Velocity.hpp"

#include "ISystem.hpp"
#include "SparseArray.hpp"

namespace System {

/// @brief This system allows our entities with the position and the velocity
/// to move using their velocity. It also checks if the entity is not colliding
/// with a solid entity while being solid to avoid them merging
class MoveSystem : public ISystem {
public:
    /// @brief Constructs an instance of a MoveSystem class
    /// @param events A ref to a Event deque
    /// @param positions A ref to a Position component SparseArray
    /// @param velocities A const ref to a Velocity component SparseArray
    /// @param solids A const ref to a Position component SparseArray
    /// @param collisions A const ref to a Collision component SparseArray
    MoveSystem(
        event::EventQueue &events, SparseArray<Component::Position> &positions,
        SparseArray<Component::Velocity> const &velocities,
        SparseArray<Component::Solid> const &solids,
        SparseArray<Component::Collision> const &collisions
    );

    /// @brief Applies the MoveSystem logic
    void operator()() override;

private:
    /// @brief Checks if the entity is colliding with another solid entity
    /// @param entity The entity which we want to check if it collides
    /// @return returns entity 0 if there a no colliding entities or the
    /// entity if there's one
    engine::Entity getCollidingSolidEntity(engine::Entity entity);

    /// @brief This methos checks whether the owner can move or if it's blocked
    /// by a solid entity
    /// @param entity The entity which we want to check if it can move
    /// @param collidingEntity The entity who colids with the owner and has a
    /// solid component
    /// @return returns true if it can move and false if it can't
    bool canMoveUp(engine::Entity entity, engine::Entity collidingEntity);
    bool canMoveDown(engine::Entity entity, engine::Entity collidingEntity);
    bool canMoveLeft(engine::Entity entity, engine::Entity collidingEntity);
    bool canMoveRight(engine::Entity entity, engine::Entity collidingEntity);

    /// @brief A const ref to a Event deque
    event::EventQueue &_events;
    /// @brief A ref to a Position component SparseArray
    SparseArray<Component::Position> &_positions;
    /// @brief A const ref to a Velocity component SparseArray
    SparseArray<Component::Velocity> const &_velocities;
    /// @brief A const ref to a Solid component SparseArray
    SparseArray<Component::Solid> const &_solids;
    /// @brief A const ref to a Collision component SparseArray
    SparseArray<Component::Collision> const &_collisions;
};
}

#endif /* !MOVE_SYSTEM_HPP_ */
