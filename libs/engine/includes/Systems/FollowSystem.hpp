/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** FollowSystem
*/

#ifndef R_TYPE_ENGINE_FOLLOW_SYSTEM_HPP_
#define R_TYPE_ENGINE_FOLLOW_SYSTEM_HPP_

#include "ISystem.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"

#include "Components/Follow.hpp"
#include "Components/Position.hpp"

namespace System {

/// @brief This system checks all entities who has a LifeTime component to kill
/// them when the registry reach their death_tick
class FollowSystem : public ISystem {
public:
    /// @brief Construct an instance of a FollowSystem class
    /// @param follows A const ref to a Follow components SparseArray
    /// @param positions A const ref to a Position components SparseArray
    /// @param registry A reference to the registry
    FollowSystem(
        SparseArray<Component::Follow> &follows,
        SparseArray<Component::Position> &positions
    );

    /// @brief an overload of the operator() which apply the FollowSystem logic
    void operator()() override;

private:
    /// @brief This method moves the owner of the Follow component to the
    /// targeted entity
    /// @param ownerFollow A ref to the Follow component of the owner entity
    /// @param ownerPosition A ref to the Position component of the owner entity
    /// @param tagetPosition A ref to the Position component of the target
    /// entity
    void moveToTarget(
        Component::Follow &follow,
        Component::Position &ownerPosition, Component::Position &tagetPosition
    );

    /// @brief A constant reference to a Follow components SparseArray
    SparseArray<Component::Follow> &_follows;
    /// @brief A constant reference to a LifeTime components SparseArray
    SparseArray<Component::Position> &_positions;
};

}
#endif /* !R_TYPE_ENGINE_FOLLOW_SYSTEM_HPP_ */
