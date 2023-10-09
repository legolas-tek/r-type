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
        auto drawable_list = _registry.get_components<Component::Drawable>();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (auto it = drawable_list.begin(); it != drawable_list.end(); ++it) {
            auto pos = _registry.get_components<Component::Position>()[it.get_entity()];

            if (_cache.find(it.get_entity()) != _cache.end()) {
                DrawTexture(_cache.at(it.get_entity())._texture, pos->_x, pos->_y, WHITE);
            } else {
                _cache.emplace(it.get_entity(), _registry._assets_paths[(*it)->_index]);
                DrawTexture(_cache.at(it.get_entity())._texture, pos->_x, pos->_y, WHITE);
            }
        }
        EndDrawing();
    }

private:
    std::unordered_map<size_t, rendering::Entity> _cache;
    engine::Registry &_registry;
};
} // namespace rendering


#endif //RENDERING_HPP
