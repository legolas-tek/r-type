/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Move System
*/

#include "Systems/ParallaxSystem.hpp"

System::ParallaxSystem::ParallaxSystem(engine::Registry &registry)
    : _registry(registry)
{
}

void System::ParallaxSystem::operator()()
{
    auto parallax_list = _registry.get_components<Component::Parallax>();
    auto &position_list = _registry.get_components<Component::Position>();
    auto drawable_list = _registry.get_components<Component::Drawable>();

    for (auto it = parallax_list.begin(); it != parallax_list.end(); ++it) {
        auto current_pos = position_list[it.get_entity()]->_x;
        auto start_pos_x = (*it)->_startPosX;
        auto width = drawable_list[it.get_entity()]->_width;
        auto scale = drawable_list[it.get_entity()]->_scale;

        if (current_pos <= start_pos_x - (width * scale)) {
            position_list[it.get_entity()]->_x = start_pos_x;
        }
    }
}
