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

namespace rendering
{
const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 450;

class Rendering {
public:
    Rendering(engine::Registry &registry);
    ~Rendering();

    void operator()()
    {
        for (auto &component : _registry.get_components<Component::Drawable>())
        // // dessiner tous les entities
        // for (const auto& pair : entities) {
        //     // std::cout << "asd" << std::endl;
        //     // std::cout << pair.second.
        // //     std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
        // }
    }
// 2d
// DrawTextureEx(_texture, _pos, _rotation, _scale, _tint);

// 3d
// DrawModelEx(_model, _pos, rotationAxis, 90.0f, scale, WHITE);
private:
    std::unordered_map<size_t, rendering::Entity> _cache;
    engine::Registry &_registry;
};
} // namespace rendering


#endif //RENDERING_HPP
