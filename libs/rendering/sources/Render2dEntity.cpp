// #include <iostream>

// #include "raylib.h"

// #include "Render2dEntity.hpp"

// Render2dEntity::Render2dEntity(std::string asset_path)
// : _pos{(Vector2){ 0.0f, 0.0f }}, _rotation{0.0f}, _scale{1.0f}, _tint{WHITE}
// {
//     _texture = LoadTexture(asset_path.c_str());

// }

// Render2dEntity::~Render2dEntity()
// {
//     UnloadTexture(_texture);
// }

// void Render2dEntity::drawEntity()
// {
//     DrawTextureEx(_texture, _pos, _rotation, _scale, _tint);
// }

// void Render2dEntity::setPos(std::optional<float> pos_x, std::optional<float> pos_y, std::optional<float> pos_z)
// {
//     if (pos_x) {
//         _pos.x = *pos_x;
//     }

//     if (pos_y) {
//         _pos.y = *pos_y;
//     }
// }

// void Render2dEntity::setScale(float scale)
// {
//     _scale = scale;
// }