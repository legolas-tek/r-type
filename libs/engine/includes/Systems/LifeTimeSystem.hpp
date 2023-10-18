/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** LifeTimeSystem
*/

#ifndef LIFETIMESYSTEM_HPP_
#define LIFETIMESYSTEM_HPP_

#include "ISystem.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"

#include "Components/LifeTime.hpp"

namespace System {

/// @brief This system checks all entities who has a LifeTime component to kill
/// them when the registry reach their death_tick
class LifeTimeSystem : public ISystem {
public:
    /// @brief Construct an instance of a LifeTimeSystem class
    /// @param life_times_ref A const ref to a LifeTime components SparseArray
    /// @param registry A reference to the registry
    LifeTimeSystem(
        SparseArray<Component::LifeTime> &life_times, engine::Registry &registry
    );

    /// @brief an overload of the operator() wich apply the LifeTimeSystem logic
    void operator()() override;

private:
    /// @brief A constant reference to a LifeTime components SparseArray
    SparseArray<Component::LifeTime> &_life_times;
    /// @brief a reference to the registry
    engine::Registry &_registry;
};

}
#endif /* !LIFETIMESYSTEM_HPP_ */
