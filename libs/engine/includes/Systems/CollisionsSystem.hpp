/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Collisions System
*/

#ifndef R_TYPE_COLLISIONSSYSTEM_HPP
#define R_TYPE_COLLISIONSSYSTEM_HPP

#include "ISystem.hpp"
#include "Registry.hpp"

#include "Components/Collision.hpp"
#include "Components/HitBox.hpp"
#include "Components/Position.hpp"

namespace System {

class CollisionsSystem : public ISystem {
public:
    CollisionsSystem(
        std::deque<std::unique_ptr<Event::IEvent>> &events,
        SparseArray<Component::Position> &positions,
        SparseArray<Component::HitBox> &hitboxes,
        SparseArray<Component::Collision> &collisions
    );

    void operator()() override;

private:
    void checkCollisions(size_t index);

    std::deque<std::unique_ptr<Event::IEvent>> &_events;
    SparseArray<Component::Position> &_positions;
    SparseArray<Component::HitBox> &_hitboxes;
    SparseArray<Component::Collision> &_collisions;
};

}
#endif // R_TYPE_COLLISIONSSYSTEM_HPP
