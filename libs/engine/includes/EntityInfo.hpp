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
    int textureIndex;
    int textureWidth;
    int textureHeight;
    int entityWidth;
    int entityHeight;
    int offset;
    int frameDuration;
    float scale;
    std::optional<int> damage;
    std::optional<size_t> lifeTime;
    std::optional<int> fireRate;
};
#endif /* !ENTITYINFO_HPP_ */
