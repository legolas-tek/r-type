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
        for (auto &component : _registry.get_components<Component::Drawable>()) {
            if(_cache.find(index) != _cache.end()) {
                DrawTexture(_cache.at(index)._texture, 0.0f, 0.0f, WHITE);
            } else {
                std::cout << "key " << index << " doesn't exists" << std::endl;
                _cache.emplace(index, _registry._assets_paths[index]);


                DrawTexture(_cache.at(index)._texture, 0.0f, 0.0f, WHITE);
            }
            index++;
        }
        EndDrawing();
    }

private:
    std::unordered_map<size_t, rendering::Entity> _cache;
    engine::Registry &_registry;
};
} // namespace rendering


#endif //RENDERING_HPP
