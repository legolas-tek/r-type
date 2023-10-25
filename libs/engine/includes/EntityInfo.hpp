/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** EntityInfo
*/

#ifndef ENTITYINFO_HPP_
#define ENTITYINFO_HPP_

#include <optional>

struct EntityInfo {
    size_t textureIndex;
    size_t textureWidth;
    size_t textureHeight;
    float entityWidth;
    float entityHeight;
    int health;
    size_t offset;
    int frameDuration;
    float scale;
    std::optional<int> damage;
    std::optional<size_t> lifeTime;
    std::optional<int> fireRate;
};
#endif /* !ENTITYINFO_HPP_ */
