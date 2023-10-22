/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** LifeTime
*/

#ifndef LIFETIME_HPP_
#define LIFETIME_HPP_

#include "Serialization/Serializable.hpp"

namespace Component {

/// @brief This component allows our entity to have a life time and will be use
/// by the lifeTime system to kill our entity whenever it has too
struct LifeTime : engine::Serializable<LifeTime> {
    /// @brief Constructs an instance of a LifeTime component and sets the
    /// tick at wich the entity should die
    /// @param lifeTime The number of ticks the entity should live
    /// @param actualTick The actual tick in the registry
    LifeTime(int lifeTime, size_t actualTick)
        : deathTick(actualTick + lifeTime)
    {
    }

    /// @brief Default constructor
    LifeTime() = default;

    /// @brief The tick at wich the entity should die
    size_t deathTick = 0;
};
}
#endif /* !LIFETIME_HPP_ */
