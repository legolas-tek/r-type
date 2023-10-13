/*
** EPITECH PROJECT, 2023
** engine
** File description:
** ColisionsSystem
*/

#ifndef PARALLAXSYSTEM_HPP_
#define PARALLAXSYSTEM_HPP_

#include "ISystem.hpp"
#include "SparseArray.hpp"

#include "Registry.hpp"

#include "Components/Drawable.hpp"
#include "Components/Parallax.hpp"
#include "Components/Position.hpp"

/// @brief This system launches an event depending if an entity hitbox hit
/// an other entity Hitbox
namespace System {

class ParallaxSystem : public ISystem {
public:
    ParallaxSystem(engine::Registry &registry)
        : _registry(registry)
    {
    }
    void operator()()
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

private:
    engine::Registry &_registry;
};
}

#endif /* !PARALLAXSYSTEM_HPP_ */
