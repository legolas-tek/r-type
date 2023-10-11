/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** logging
*/

#ifndef LOGGING_HPP_
#define LOGGING_HPP_

#include "ISystem.hpp"

#include "SparseArray.hpp"

#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

/// @brief This system is juste a log system made for debug, it prints
// the positions and velocities values
namespace System {
class Logging : public ISystem {
public:
    Logging(
        SparseArray<Component::Position> const &positions,
        SparseArray<Component::Velocity> const &velocities
    )
        : _positions(positions)
        , _velocities(velocities)
    {
    }
    Logging(System::Logging const &other) = delete;

    void operator()() override
    {
        for (size_t i = 0; i < _positions.size() && i < _velocities.size();
             i++) {
            auto const &pos = _positions[i];
            auto const &vel = _velocities[i];
            if (pos.has_value() && vel.has_value()) {
                std ::cerr << i << " : Position = { " << pos.value()._x << " , "
                           << pos.value()._y << " } , Velocity = { "
                           << vel.value()._vx << " , " << vel.value()._vy
                           << " } " << std ::endl;
            }
        }
    }

private:
    SparseArray<Component::Position> const &_positions;
    SparseArray<Component::Velocity> const &_velocities;
};
}

#endif /* !LOGGING_HPP_ */
