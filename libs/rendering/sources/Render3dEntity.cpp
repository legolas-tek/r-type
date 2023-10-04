// #include <iostream>

// #include "raylib.h"

// #include "Render3dEntity.hpp"

// Render3dEntity::Render3dEntity(std::string object_path, std::string asset_path)
// : _pos{(Vector3){ 0.0f, 0.0f, 0.0f }}, _rotation{90.0f}, _scale{1.0f}, _tint{WHITE}
// {
//     _model = LoadModel(object_path.c_str());
//     Texture2D texture = LoadTexture(asset_path.c_str());
//     _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
//     // _texture = LoadTexture(asset_path.c_str());

// }

// Render3dEntity::~Render3dEntity()
// {
//     UnloadTexture(_texture);
// }

// void Render3dEntity::drawEntity()
// {
//         Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f }; // Y축
//         Vector3 scale = { 1.0f, 1.0f, 1.0f }; // Y축

//     DrawModelEx(_model, _pos, rotationAxis, 90.0f, scale, WHITE);
//     // DrawTextureEx(_texture, _pos, _rotation, _scale, _tint);
// }

// void Render3dEntity::setPos(std::optional<float> pos_x, std::optional<float> pos_y, std::optional<float> pos_z)
// {
//     if (pos_x) {
//         _pos.x = *pos_x;
//     }

//     if (pos_y) {
//         _pos.y = *pos_y;
//     }

//     if (pos_z) {
//         _pos.z = *pos_z;
//     }
// }

// void Render3dEntity::setScale(float scale)
// {
//     // _scale = scale;
// }

// Model Render3dEntity::getModel()
// {
//     return _model;
// }

// void setRotationAxis(std::optional<float> pos_x, std::optional<float> pos_y, std::optional<float> pos_z)
// {
//     // if (pos_x) {
//     //     _rotationAxis.x = *pos_x;
//     // }

//     // if (pos_y) {
//     //     _rotationAxis.y = *pos_y;
//     // }

//     // if (pos_z) {
//     //     _rotationAxis.z = *pos_z;
//     // }
// }
