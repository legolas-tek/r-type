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
        if (animationElement._texture_width - animationElement._current_offset
            <= animationElement._entity_width) {
            animationElement._current_offset = 0;
            continue;
        }

        if (_registry.getTick() % animationElement._duration == 0) {
            animationElement._current_offset += animationElement._offset;
        }
    }
}
