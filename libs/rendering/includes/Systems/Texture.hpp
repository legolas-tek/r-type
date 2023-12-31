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
#include "Rendering.hpp"
#include "SparseArray.hpp"

#include "raylib.h"
#include <unordered_map>
#include <variant>

namespace rendering::system {

struct CameraInfo {
    Vector3 pos;
    Vector3 target;
    Vector3 up;
    float fovy;
    int projection;
};

/// @brief A system for redering textures.
struct Texture : public ISystem {
    /// @brief Constructor for the Texture system.
    /// @param registry A reference to the game registry.
    /// @param drawables A reference to the drawables component storage.
    /// @param animations A reference to the animations component storage.
    /// @param positions A reference to the positions component storage.
    Texture(
        engine::Registry &registry, SparseArray<Component::Drawable> &drawables,
        SparseArray<Component::Animation> &animations,
        SparseArray<Component::Position> &positions, CameraInfo cameraInfo
    );

    /// @brief Destructor for the Texture system.
    ~Texture() override;

    /// @brief Operator to execute the Texture system.
    void operator()() override;

private:
    engine::Registry &_registry;
    SparseArray<Component::Drawable> &_drawables;
    SparseArray<Component::Animation> &_animations;
    SparseArray<Component::Position> &_positions;
    std::vector<std::variant<Texture2D, Model>> _cache;
    Camera _camera = { 0 };
};

} // namespace rendering::system

#endif // R_TYPE_TEXTURE_HPP
