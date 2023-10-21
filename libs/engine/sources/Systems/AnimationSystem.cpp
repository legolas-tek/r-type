/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Move System
*/

#include "Components/Animation.hpp"

#include "Systems/AnimationSystem.hpp"

System::AnimationSystem::AnimationSystem(engine::Registry &registry)
    : _registry(registry)
{
}

void System::AnimationSystem::operator()()
{
    auto &animation_list = _registry.get_components<Component::Animation>();

    for (auto it = animation_list.begin(); it != animation_list.end(); ++it) {
        auto &animationElement = animation_list[it.get_entity()].value();
        if (animationElement._textureWidth - animationElement._currentOffset
            <= animationElement._entityWidth) {
            animationElement._currentOffset = 0;
            continue;
        }

        if (_registry.getTick() % animationElement._duration == 0) {
            animationElement._currentOffset += animationElement._offset;
        }
    }
}
