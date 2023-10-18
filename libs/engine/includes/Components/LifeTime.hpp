/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** LifeTime
*/

#ifndef LIFETIME_HPP_
#define LIFETIME_HPP_

#include "Serializable.hpp"

namespace Component {

/// @brief This component allows our entity to have a life time and will be use
/// by the lifeTime system to kill our entity whenever it has too
struct LifeTime : Serializable<LifeTime> {
    /// @brief Constructor an instance of a LifeTime component and sets the
    /// tick at wich the entity should die
    /// @param life_time The number of ticks the entity should live
    /// @param actual_tick The actual tick in the registry
    LifeTime(int life_time, size_t actual_tick)
        : death_tick(actual_tick + life_time)
    {
    }

    /// @brief Default constructor
    LifeTime() = default;

    /// @brief The tick at wich the entity should die

    size_t death_tick = 0;
};

}
#endif /* !LIFETIME_HPP_ */
