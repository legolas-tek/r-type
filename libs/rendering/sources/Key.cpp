/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Key
*/

#include "Key.hpp"
#include "raylib.h"

rendering::system::Key::Key(engine::Registry &registry)
    : _registry(registry)
{
}

rendering::system::Key::~Key()
{
}

void rendering::system::Key::operator()()
{
    auto &velocity_list = _registry.get_components<Component::Velocity>();
    auto &controllable_list
        = _registry.get_components<Component::Controllable>();

    for (auto it = velocity_list.begin(); it != velocity_list.end(); ++it) {
        bool isControllable = controllable_list[it.get_entity()].has_value();

        if (isControllable) {
            velocity_list[it.get_entity()]->_vx = 0.0f;
            velocity_list[it.get_entity()]->_vy = 0.0f;
            if (IsKeyDown(KEY_W) || IsKeyDown(KEY_Z)) {
                velocity_list[it.get_entity()]->_vx += 0.0f;
                velocity_list[it.get_entity()]->_vy += -0.1f;
            }
            if (IsKeyDown(KEY_A) || IsKeyDown(KEY_Q)) {
                velocity_list[it.get_entity()]->_vx += -0.1f;
                velocity_list[it.get_entity()]->_vy += 0.0f;
            }
            if (IsKeyDown(KEY_S)) {
                velocity_list[it.get_entity()]->_vx += 0.0f;
                velocity_list[it.get_entity()]->_vy += 0.1f;
            }
            if (IsKeyDown(KEY_D)) {
                velocity_list[it.get_entity()]->_vx += 0.1f;
                velocity_list[it.get_entity()]->_vy += 0.0f;
            }
        }
    }
}
