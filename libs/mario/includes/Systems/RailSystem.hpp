/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** RailSystem
*/

#ifndef RAILBACKGROUNDSYSTEM_HPP_
#define RAILBACKGROUNDSYSTEM_HPP_

#include "ISystem.hpp"

#include "SparseArray.hpp"

#include "Components/Collision.hpp"
#include "Components/Position.hpp"
#include "Components/Rail.hpp"
#include "Components/Velocity.hpp"

#include "Rendering.hpp"

#include "MarioGame.hpp"

namespace System {
class RailSystem : public ISystem {
public:
    RailSystem(
        SparseArray<Component::Rail> &rails,
        SparseArray<Component::Velocity> &velocities,
        SparseArray<Component::Position> &positions,
        SparseArray<Component::Drawable> &drawables
    );

    void operator()() override;

protected:
private:
    SparseArray<Component::Rail> &_rails;
    SparseArray<Component::Velocity> &_velocities;
    SparseArray<Component::Position> &_positions;
    SparseArray<Component::Drawable> &_drawables;
};
}

#endif /* !RAILBACKGROUNDSYSTEM_HPP_ */
