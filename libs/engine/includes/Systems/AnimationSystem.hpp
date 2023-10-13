/*
** EPITECH PROJECT, 2023
** engine
** File description:
** ColisionsSystem
*/

#ifndef ANIMATIONSYSTEM_HPP_
#define ANIMATIONSYSTEM_HPP_

#include "ISystem.hpp"
#include "SparseArray.hpp"

#include "Registry.hpp"

#include "Components/Animation.hpp"

/// @brief This system launches an event depending if an entity hitbox hit
/// an other entity Hitbox
namespace System {

class AnimationSystem : public ISystem {
public:
    AnimationSystem(engine::Registry &registry)
    : _registry(registry)
    {
    }
    // ~AnimationSystem();
    void operator()()
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

private:
    engine::Registry &_registry;
};
}

#endif /* !ANIMATIONSYSTEM_HPP_ */
