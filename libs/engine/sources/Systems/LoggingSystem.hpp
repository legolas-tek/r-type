/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** logging
*/

#ifndef LOGGING_HPP_
#define LOGGING_HPP_

#include "ISystem.hpp"

#include "Registry.hpp"

#include "Components/PositionComponent.hpp"
#include "Components/VelocityComponent.hpp"

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
        for (auto const &it : _positions)
            if (it.has_value())
                std::cout << "first test : x = " << it->_x << " y = " << it->_y
                          << std::endl;
        for (auto it : positions)
            if (it.has_value())
                std::cout << "second test : x = " << it->_x << " y = " << it->_y
                          << std::endl;
    }
    Logging(System::Logging const &other) = delete;

    void operator()()
    {
        for (size_t i = 0; i < _positions.size() && i < _velocities.size();
             i++) {
            auto const &pos = _positions[i];
            auto const &vel = _velocities[i];
            if (pos.has_value() && vel.has_value()) {
                std::cout << "Condition validated" << std::endl;
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