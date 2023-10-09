/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Rendering
*/

#ifndef RENDERING_HPP
    #define RENDERING_HPP

#include <unordered_map>
#include <iostream>

#include "raylib.h"
#include "Entity.hpp"
#include "RenderEntity.hpp"
#include "Registry.hpp"
#include "ISystem.hpp"
#include "Components/Position.hpp"

#include "Components/Drawable.hpp"

namespace rendering
{
const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 450;

class Rendering : public ISystem {
public:
    Rendering(engine::Registry &registry);
    ~Rendering();

    void operator()()
    {
        std::size_t index = 0;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (auto it = _registry.get_components<Component::Drawable>().begin(); it != _registry.get_components<Component::Drawable>().end(); ++it) {
            // std::cout << "get_entity " << it.get_entity() << std::endl;
            // std::cout << "index: " << (*it)->_index << std::endl;
            // std::cout << _registry.get_components<Component::Position>()[it.get_entity()]->_x << " " << _registry.get_components<Component::Position>()[it.get_entity()]->_y << std::endl;

            auto pos = _registry.get_components<Component::Position>()[it.get_entity()];
            // if (pos.has_value()) {
            //     std::cout << "has value" << std::endl;
            // } else {
            //     std::cout << "no has value" << std::endl;
            // }

            if (_cache.find(it.get_entity()) != _cache.end()) {
                DrawTexture(_cache.at(it.get_entity())._texture, pos->_x, pos->_y, WHITE);
            } else {
                _cache.emplace(it.get_entity(), _registry._assets_paths[(*it)->_index]);
                DrawTexture(_cache.at(it.get_entity())._texture, pos->_x, pos->_y, WHITE);
            }
            // if (auto asset
            //     = _registry.get_components<Component::Drawable>()[it.get_entity()]) {
            //     std::cout << asset.value() << std::endl;
            // }
            // if
            // (regi.get_components<Component::drawable>()[it.get_entity()].has_value())
            // regi.get_components<Component::drawable>()[it.get_entity()]->_sprite.getSprite().setPosition((*it)->_x,
            // (*it)->_y);
        }
        // for (auto &component : _registry.get_components<Component::Drawable>()) {
        //     // get components <Drawable > () [entity]._index
        //     std::cout << _registry.get_components<Component::Drawable>()[_registry.get_components<Component::Drawable>().begin().get_entity()]->_index << std::endl;
        //     std::cout << "index: " << index << std::endl;
        //     if (_cache.find(index) != _cache.end()) {
        //         DrawTexture(_cache.at(index)._texture, 0.0f, 0.0f, WHITE);
        //     } else {
        //         _cache.emplace(index, _registry._assets_paths[index]);

        //     }
        //     index++;
        // }
        EndDrawing();
    }

private:
    std::unordered_map<size_t, rendering::Entity> _cache;
    engine::Registry &_registry;
};
} // namespace rendering


#endif //RENDERING_HPP
