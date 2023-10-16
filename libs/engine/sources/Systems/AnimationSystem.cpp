/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Move System
*/

#include "Components/Animation.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

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
        // std::cout << "entity " << it.get_entity() << " offset " <<
        // animationElement._current_offset << std::endl;
        if (animationElement._texture_width - animationElement._current_offset
            <= animationElement._entity_width) {
            // std::cout << "asd" << std::endl;
            animationElement._current_offset = 0;
            continue;
        }
        animationElement._current_offset += animationElement._offset;
        // if (animationElement._current_offset)
        // if (animationElement._current_index < animationElement._spriteNum) {
        //     animationElement._current_index++;
        // } else {
        //     animationElement._current_index = 0;
        // }
    }
    // _offset
    // _current_offset
}
