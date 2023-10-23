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
    for (auto asset : _registry._assets_paths) {
        _cache.push_back(LoadTexture(asset.c_str()));
    }
}

rendering::system::Texture::~Texture()
{
    for (auto &texture : _cache)
        UnloadTexture(texture);
}

void rendering::system::Texture::operator()()
{
    std::vector<engine::Entity> entityList;

    for (auto it = _drawables.begin(); it != _drawables.end(); ++it) {
        if (_positions[it.get_entity()]) {
            entityList.emplace_back(it.get_entity());
        }
    }

    std::sort(entityList.begin(), entityList.end(), [this](size_t a, size_t b) {
        return _positions[a]->_z < _positions[b]->_z;
    });

    for (auto &entity : entityList) {
        auto pos = _positions[entity];
        auto anim = _animations[entity];
        size_t textureIndex = _drawables[entity]->_index;

        Texture2D texture = _cache[textureIndex];
        Rectangle sourceRec
            = { 0.0f, _drawables[entity]->_yOrigin, _drawables[entity]->_width,
                _drawables[entity]->_height };

        if (anim.has_value())
            sourceRec.x = float(anim.value()._currentOffset);

        auto scaledWidth = sourceRec.width * _drawables[entity]->_scale;
        auto scaledHeight = sourceRec.height * _drawables[entity]->_scale;

        Rectangle destRec
            = { pos->_x - scaledWidth / 2, pos->_y - scaledHeight / 2,
                scaledWidth, scaledHeight };

        DrawTexturePro(texture, sourceRec, destRec, { 0, 0 }, 0.0f, WHITE);
    }
}
