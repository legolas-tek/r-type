/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Move System
*/

#include "Systems/MoveSystem.hpp"
#include "Events/Collision.hpp"

System::MoveSystem::MoveSystem(
    std::deque<std::unique_ptr<Event::IEvent>> const &events,
    SparseArray<Component::Position> &positions,
    SparseArray<Component::Velocity> const &velocities,
    SparseArray<Component::Solid> const &solids,
    SparseArray<Component::Collision> const &collisions
)
    : _events(events)
    , _positions(positions)
    , _velocities(velocities)
    , _solids(solids)
    , _collisions(collisions)
{
}

void System::MoveSystem::operator()()
{
    for (auto it = _positions.begin(); it != _positions.end(); ++it) {
        auto &pos = **it;
        auto &vel = _velocities[it.get_entity()];
        engine::Entity collidingEntity
            = getCollidingSolidEntity(it.get_entity());

        if (vel && canMove(collidingEntity, vel.value(), pos)) {
            pos._x += vel->_vx;
            pos._y += vel->_vy;
        }
    }
}

engine::Entity System::MoveSystem::getCollidingSolidEntity(
    engine::Entity entity
)
{
    if (not _solids[entity] or not _collisions[entity])
        return engine::Entity(0);

    for (auto &event : _events) {
        auto collision = dynamic_cast<Event::Collision *>(event.get());

        if (not collision)
            continue;

        if (collision->entity == entity)
            return collision->secondEntity;
    }

    return engine::Entity(0);
}

bool System::MoveSystem::canMove(
    engine::Entity collidingEntity, Component::Velocity const &velocity,
    Component::Position &position
)
{
    if (collidingEntity == 0 || !_positions[collidingEntity]
        || !_solids[collidingEntity])
        return true;
    auto collidingEntityPos = _positions[collidingEntity].value();

    if (position._x < collidingEntityPos._x && velocity._vx > 0)
        return false;
    if (position._x > collidingEntityPos._x && velocity._vx < 0)
        return false;
    if (position._y < collidingEntityPos._y && velocity._vy > 0)
        return false;
    if (position._y > collidingEntityPos._y && velocity._vy < 0)
        return false;
    return true;
}
