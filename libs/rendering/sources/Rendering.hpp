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

namespace rendering
{
const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 450;

class Rendering {
public:
    Rendering();
    ~Rendering();

    void operator()()
    {
        // dessiner tous les entities
        for (const auto& pair : entities) {
            std::cout << "asd" << std::endl;
        //     std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
        }
    }
// 2d
// DrawTextureEx(_texture, _pos, _rotation, _scale, _tint);

// 3d
// DrawModelEx(_model, _pos, rotationAxis, 90.0f, scale, WHITE);

    std::unordered_map<size_t, rendering::Entity> entities;

    // unordormap<entity de engine, entity >
};
} // namespace rendering


#endif //RENDERING_HPP
