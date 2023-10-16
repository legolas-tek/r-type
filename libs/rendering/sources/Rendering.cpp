
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
    auto position_list = _registry.get_components<Component::Position>();
    std::vector<size_t> entity_list;

    for (auto it = drawable_list.begin(); it != drawable_list.end(); ++it) {
        entity_list.push_back(it.get_entity());
    }

    std::sort(
        entity_list.begin(), entity_list.end(),
        [&position_list](size_t a, size_t b) {
            return position_list[a]->_z < position_list[b]->_z;
        }
    );

    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (size_t entity : entity_list) {
        auto pos = _registry.get_components<Component::Position>()[entity];
        if (_cache.find(entity) == _cache.end()) {
            _cache.emplace(
                entity, _registry._assets_paths[drawable_list[entity]->_index]
            );
        }
        Texture2D texture = _cache.at(entity)._texture;
        Rectangle sourceRec = { 0.0f, 0.0f, drawable_list[entity]->_width,
                                drawable_list[entity]->_height };
        if (animation_list[entity].has_value()) {
            auto rect_x = animation_list[entity].value()._current_offset;
            sourceRec.x = rect_x;
        }
        float scale = drawable_list[entity]->_scale;
        Rectangle destRec = { pos->_x, pos->_y, sourceRec.width * scale,
                              sourceRec.height * scale };
        Vector2 origin = { 0, 0 };
        float rotation = 0.0f;
        Color tint = WHITE;

        DrawTexturePro(texture, sourceRec, destRec, origin, rotation, tint);
    }
    EndDrawing();
}
