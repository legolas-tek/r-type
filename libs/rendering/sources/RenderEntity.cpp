/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Entity
*/

#include "RenderEntity.hpp"

rendering::Entity::Entity(std::string texture_path)
{
    _texture = LoadTexture(texture_path.c_str());
}

rendering::Entity::~Entity()
{
    UnloadTexture(_texture);
}
