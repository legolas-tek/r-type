
/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Rendering
*/

#include "Rendering.hpp"

rendering::system::Rendering::Rendering(engine::Registry &registry)
    : _registry(registry)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib background scrolling");
}

rendering::system::Rendering::~Rendering()
{
    CloseWindow();
}

void rendering::system::Rendering::operator()()
{
    auto drawable_list = _registry.get_components<Component::Drawable>();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (auto it = drawable_list.begin(); it != drawable_list.end(); ++it) {
        auto pos
            = _registry.get_components<Component::Position>()[it.get_entity()];

        if (_cache.find(it.get_entity()) != _cache.end()) {
            DrawTexture(
                _cache.at(it.get_entity())._texture, pos->_x, pos->_y, WHITE
            );
        } else {
            _cache.emplace(
                it.get_entity(), _registry._assets_paths[(*it)->_index]
            );

            DrawTexture(
                _cache.at(it.get_entity())._texture, pos->_x, pos->_y, WHITE
            );
        }
    }
    EndDrawing();
}
