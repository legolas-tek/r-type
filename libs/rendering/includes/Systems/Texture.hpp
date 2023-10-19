/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Text
*/

#ifndef R_TYPE_TEXTURE_HPP
#define R_TYPE_TEXTURE_HPP

#include "Components/Animation.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "ISystem.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"

#include "raylib.h"
#include <unordered_map>

namespace rendering::system {

struct Texture : public ISystem {
    Texture(
        engine::Registry &registry, SparseArray<Component::Drawable> &drawables,
        SparseArray<Component::Animation> &animations,
        SparseArray<Component::Position> &positions
    );
    ~Texture() override;
    void operator()() override;

private:
    bool isTextureLoaded(size_t id);
    engine::Registry &_registry;
    SparseArray<Component::Drawable> &_drawables;
    SparseArray<Component::Animation> &_animations;
    SparseArray<Component::Position> &_positions;
    std::unordered_map<size_t, Texture2D> _cache;
};

}

#endif // R_TYPE_TEXTURE_HPP
