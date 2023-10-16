
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
    auto animation_list = _registry.get_components<Component::Animation>();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (auto it = drawable_list.begin(); it != drawable_list.end(); ++it) {
        auto pos
            = _registry.get_components<Component::Position>()[it.get_entity()];

        if (_cache.find(it.get_entity()) == _cache.end()) {
            _cache.emplace(
                it.get_entity(), _registry._assets_paths[(*it)->_index]
            );
        }
        Texture2D texture = _cache.at(it.get_entity())._texture;
        Rectangle sourceRec = { 0.0f, 0.0f, (*it)->_width, (*it)->_height };
        if (animation_list[it.get_entity()].has_value()) {
            std::cout << animation_list[it.get_entity()].value()._current_offset
                      << std::endl;
            auto rect_x
                = animation_list[it.get_entity()].value()._current_offset;
            sourceRec.x = rect_x;
        }
        float scale = (*it)->_scale;
        Rectangle destRec = { pos->_x, pos->_y, sourceRec.width * scale,
                              sourceRec.height * scale };
        Vector2 origin = { 0, 0 };
        float rotation = 0.0f;
        Color tint = WHITE;

        DrawTexturePro(texture, sourceRec, destRec, origin, rotation, tint);
    }
    EndDrawing();
}
