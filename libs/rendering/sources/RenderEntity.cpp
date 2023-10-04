/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Entity
*/

#include "RenderEntity.hpp"

rendering::Entity::Entity(std::string texture_path, std::optional<std::string> model_path)
{
    _texture = LoadTexture(texture_path.c_str());

    if (model_path) {
        _model = LoadModel(model_path->c_str());
        _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
    }
}

rendering::Entity::~Entity()
{
    UnloadTexture(_texture);

    if (_model.materialCount > 0) {
        UnloadModel(_model);
    }
}
