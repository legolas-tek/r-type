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
    // ~ParallaxSystem();
    void operator()()
    {
        auto parallax_list = _registry.get_components<Component::Parallax>();
        auto & position_list = _registry.get_components<Component::Position>();
        // DrawTextureRec(scarfy, frameRec, position, WHITE);  // Draw part of the texture
        for (auto it = parallax_list.begin(); it != parallax_list.end(); ++it) {
            auto current_pos = position_list[it.get_entity()]->_x;
            auto start_pos_x = parallax_list[it.get_entity()]->_startPosX;
            auto testure_width = parallax_list[it.get_entity()]->_width;

            if (current_pos <= start_pos_x - testure_width) {
                position_list[it.get_entity()]->_x = start_pos_x;
                std::cout << "asdaaaasdaaaasdaaa" << std::endl;
            }
            // parallax_list[it.get_entity()]->_startPosX
            // std::cout << "parallax target: " << it.get_entity() << " current pos: " << position_list[it.get_entity()]->_x << " " << position_list[it.get_entity()]->_y << std::endl;

        }
        // std::cout << "parallax" << std::endl;
        // func logic
    }

private:
    engine::Registry &_registry;
};
}

#endif /* !PARALLAXSYSTEM_HPP_ */
