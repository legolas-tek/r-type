/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Texture System
*/

#include "Systems/Texture.hpp"
#include <algorithm>

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

bool rendering::system::Texture::isTextureLoaded(size_t id)
{
    return _cache.find(id) != _cache.end();
}

void rendering::system::Texture::operator()()
{
    std::vector<engine::Entity> entityList;

    for (auto it = _drawables.begin(); it != _drawables.end(); ++it)
        entityList.push_back(it.get_entity());

    std::sort(entityList.begin(), entityList.end(), [this](size_t a, size_t b) {
        return _positions[a]->_z < _positions[b]->_z;
    });

    for (auto &entity : entityList) {
        auto pos = _positions[entity];
        auto anim = _animations[entity];

        if (not isTextureLoaded(entity))
            _cache[entity] = LoadTexture(
                _registry._assets_paths[_drawables[entity]->_index].c_str()
            );

        Texture2D texture = _cache[entity];
        Rectangle sourceRec = { 0.0f, 0.0f, _drawables[entity]->_width,
                                _drawables[entity]->_height };

        if (anim.has_value())
            sourceRec.x = (float) anim.value()._current_offset;

        Rectangle destRec
            = { pos->_x, pos->_y, sourceRec.width * _drawables[entity]->_scale,
                sourceRec.height * _drawables[entity]->_scale };

        DrawTexturePro(texture, sourceRec, destRec, { 0, 0 }, 0.0f, WHITE);
    }
}
