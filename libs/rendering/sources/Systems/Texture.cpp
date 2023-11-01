/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Texture System
*/

#include "Systems/Texture.hpp"
#include <algorithm>
#include <iostream>

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
        if (!asset.path_3d) {
            _cache.push_back(LoadTexture(asset.path_2d.c_str()));
        } else {
            Model tower = LoadModel(asset.path_3d->c_str());
            Texture2D texture = LoadTexture(asset.path_2d.c_str());
            tower.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
            _cache.push_back(tower);
        }
    }
}

rendering::system::Texture::~Texture()
{
    for (auto &item : _cache) {
        std::visit(
            [](auto &&arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, Texture2D>) {
                    UnloadTexture(arg);
                } else if constexpr (std::is_same_v<T, Model>) {
                    UnloadModel(arg);
                }
            },
            item
        );
    }
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

        if (std::holds_alternative<Texture2D>(_cache[textureIndex])) {
            Texture2D texture = std::get<Texture2D>(_cache[textureIndex]);

            Rectangle sourceRec
                = { 0.0f, _drawables[entity]->_yOrigin,
                    _drawables[entity]->_width, _drawables[entity]->_height };

            if (anim.has_value())
                sourceRec.x = float(anim.value()._currentOffset);

            auto scaledWidth = sourceRec.width * _drawables[entity]->_scale;
            auto scaledHeight = sourceRec.height * _drawables[entity]->_scale;

            Rectangle destRec
                = { pos->_x - scaledWidth / 2, pos->_y - scaledHeight / 2,
                    scaledWidth, scaledHeight };

            DrawTexturePro(texture, sourceRec, destRec, { 0, 0 }, 0.0f, WHITE);
        } else if (std::holds_alternative<Model>(_cache[textureIndex])) {
            Vector3 towerPos = { 0.0f, 0.0f, 0.0f };

            Camera camera = { 0 };
            camera.position = (Vector3) { 20.0f, 20.0f, 20.0f };
            camera.target = (Vector3) { 0.0f, 8.0f, 0.0f };
            camera.up = (Vector3) { 0.0f, 1.6f, 0.0f };
            camera.fovy = 45.0f;
            camera.projection = CAMERA_PERSPECTIVE;

            Model model3d = std::get<Model>(_cache[textureIndex]);

            BeginMode3D(camera);

            DrawModel(model3d, towerPos, 1.0f, WHITE);
            EndMode3D();
        }
    }
}
