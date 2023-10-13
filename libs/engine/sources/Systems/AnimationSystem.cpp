/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Move System
*/

#include "Systems/AnimationSystem.hpp"

System::AnimationSystem::AnimationSystem(engine::Registry &registry)
    : _registry(registry)
{
}

void System::AnimationSystem::operator()()
{
    auto &animation_list = _registry.get_components<Component::Animation>();
    auto drawable_list = _registry.get_components<Component::Drawable>();

    for (auto it = animation_list.begin(); it != animation_list.end(); ++it) {
        auto &animationElement = animation_list[it.get_entity()].value();
        if (animationElement._current_index < animationElement._spriteNum) {
            animationElement._current_index++;
        } else {
            animationElement._current_index = 0;
        }
    }
}
