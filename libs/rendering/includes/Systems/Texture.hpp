/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Texture
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

/// @brief A system for handling textures in the R-Type game.
struct Texture : public ISystem {
    /// @brief Constructor for the Texture system.
    /// @param registry A reference to the game registry.
    /// @param drawables A reference to the drawables component storage.
    /// @param animations A reference to the animations component storage.
    /// @param positions A reference to the positions component storage.
    Texture(
        engine::Registry &registry, SparseArray<Component::Drawable> &drawables,
        SparseArray<Component::Animation> &animations,
        SparseArray<Component::Position> &positions
    );

    /// @brief Destructor for the Texture system.
    ~Texture() override;

    /// @brief Operator to execute the Texture system.
    void operator()() override;

private:
    /// @brief Check if a texture is already loaded.
    /// @param id The unique ID of the texture.
    /// @return True if the texture is loaded, false otherwise.
    bool isTextureLoaded(size_t id);

    engine::Registry &_registry;
    SparseArray<Component::Drawable> &_drawables;
    SparseArray<Component::Animation> &_animations;
    SparseArray<Component::Position> &_positions;
    std::unordered_map<size_t, Texture2D> _cache;
};

} // namespace rendering::system

#endif // R_TYPE_TEXTURE_HPP
