/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Texture System
*/

#include "Systems/Texture.hpp"

rendering::system::Texture::Texture(
    engine::Registry &registry, SparseArray<Component::Drawable> &drawables,
    SparseArray<Component::Animation> &animations,
    SparseArray<Component::Position> &positions
)
    : _registry(registry)
    , _drawables(drawables)
    , _animations(animations)
    , _positions(positions)
{
}

rendering::system::Texture::~Texture()
{
    for (auto &texture : _cache)
        UnloadTexture(texture.second);
}

bool rendering::system::Texture::TextureIsLoaded(size_t id)
{
    return _cache.find(id) != _cache.end();
}

void rendering::system::Texture::operator()()
{
    auto &pos_list = _registry.get_components<Component::Position>();
    for (auto it = _drawables.begin(); it != _drawables.end(); ++it) {
        auto id = it.get_entity();
        auto pos = pos_list[id];
        auto anim = _animations[id];

        if (not TextureIsLoaded(id))
            _cache[id]
                = LoadTexture(_registry._assets_paths[(*it)->_index].c_str());

        Texture2D texture = _cache[id];
        Rectangle sourceRec = { 0.0f, 0.0f, (*it)->_width, (*it)->_height };

        if (anim.has_value())
            sourceRec.x = (float) anim.value()._current_offset;

        Rectangle destRec = { pos->_x, pos->_y, sourceRec.width * (*it)->_scale,
                              sourceRec.height * (*it)->_scale };

        DrawTexturePro(texture, sourceRec, destRec, { 0, 0 }, 0.0f, WHITE);
    }
}
