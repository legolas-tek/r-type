/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** RailSystem
*/

#include "Systems/RailSystem.hpp"

System::RailSystem::RailSystem(
    SparseArray<Component::Rail> &rails,
    SparseArray<Component::Velocity> &velocities,
    SparseArray<Component::Position> &positions,
    SparseArray<Component::Drawable> &drawables
)
    : _rails(rails)
    , _velocities(velocities)
    , _positions(positions)
    , _drawables(drawables)
{
}

void System::RailSystem::operator()()
{
    // engine::Entity staticEntity;
    float velocity_x = 0.0f;
    float velocity_y = 0.0f;
    size_t entity;
    bool isAtEnd = false;
    bool canMove = true;

    for (auto it = _rails.begin(); it != _rails.end(); it++) {
        (*it)->type;
        if ((*it)->type == Component::RailType::STATIC) {
            auto velocity = _velocities[it.get_entity()];
            velocity_x = velocity->_vx;
            velocity_y = velocity->_vy;
            entity = it.get_entity();
            break;
        }
    }
    for (auto it = _rails.begin(); it != _rails.end(); it++) {
        if ((*it)->type == Component::RailType::DYNAMIC_BACKGROUND) {
            auto pos = _positions[it.get_entity()];
            auto draw = _drawables[it.get_entity()];

            if (0.0 <= pos->_x - (draw->_width * draw->_scale / 2)
                && velocity_x < 0) {
                _velocities[it.get_entity()]->_vx = 0.0f;
                isAtEnd = false;
                canMove = false;
            } else if (pos->_x <= -((draw->_width * draw->_scale) - static_cast<float>(rendering::system::SCREEN_WIDTH)) + draw->_width * draw->_scale / 2 && velocity_x > 0) {
                _velocities[it.get_entity()]->_vx = 0.0f;
                canMove = false;
                isAtEnd = false;
            } else {
                _velocities[it.get_entity()]->_vx = -velocity_x;
                isAtEnd = true;
            }
        } else if ((*it)->type == Component::RailType::DYNAMIC) {
            if (!canMove) {
                _velocities[it.get_entity()]->_vx = 0;
            } else {
                _velocities[it.get_entity()]->_vx = -velocity_x;
            }
        }
    }
    if (isAtEnd) {
        _velocities[entity]->_vx = 0.0f;
    }
}
