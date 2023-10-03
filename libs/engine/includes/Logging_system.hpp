/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** logging
*/

#ifndef LOGGING_HPP_
#define LOGGING_HPP_

#include "ISystem.hpp"
#include "position.hpp"
#include "velocity.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

namespace System {

    class Logging : public ISystem {
        public:
            Logging(sparse_array<Component::position> const &positions,
                    sparse_array<Component::velocity> const &velocities) :
                    _positions(positions), _velocities(velocities) {}
            Logging(System::Logging const &other) = delete;

            void operator()() {
                for (size_t i = 0; i < _positions.size() && i < _velocities.size(); i++) {
                		auto const &pos = _positions[i];
                		auto const &vel = _velocities[i];
                		if (pos.has_value() && vel.has_value()) {
                			std ::cerr << i << " : Position = { " << pos.value()._x << " , " << pos.value()._y << " } , Velocity = { " << vel.value()._vx << " , " << vel.value()._vy << " } " << std ::endl;
                		}
            	}
            }

        private:
            sparse_array<Component::position> const &_positions;
            sparse_array<Component::velocity> const &_velocities;
    };
}

#endif /* !LOGGING_HPP_ */
