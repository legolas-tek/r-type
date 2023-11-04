/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** RailSystem
*/

#include "Systems/RailSystem.hpp"

#include <iostream>

System::RailSystem::RailSystem(
    SparseArray<Component::Rail> &rails,
    SparseArray<Component::Velocity> &velocities
)
    : _rails(rails)
    , _velocities(velocities)
{
}

void System::RailSystem::operator()()
{
    // engine::Entity staticEntity;
    float velocity_x = 0.0f;
    float velocity_y = 0.0f;

    for (auto it = _rails.begin(); it != _rails.end(); it++) {
        (*it)->type;
        if ((*it)->type == Component::RailType::SATIC) {
            // engine::Entity staticEntity = it.get_entity();
            auto velocity = _velocities[it.get_entity()];
            velocity_x = velocity->_vx;
            velocity_y = velocity->_vy;
            _velocities[it.get_entity()]->_vx = 0.0f;
            std::cout << "entity " << it.get_entity() << " " << velocity_x
                      << " " << velocity_y << std::endl;
        }
    }
    for (auto it = _rails.begin(); it != _rails.end(); it++) {
        if ((*it)->type == Component::RailType::DYNAMIC) {
            _velocities[it.get_entity()]->_vx = -velocity_x;
            std::cout << "aaa" << it.get_entity() << std::endl;
        }
    }
}
