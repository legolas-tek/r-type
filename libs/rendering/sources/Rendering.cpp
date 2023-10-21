
/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Rendering
*/

#include "Rendering.hpp"

#include "Systems/Focusable.hpp"
#include "Systems/Text.hpp"
#include "Systems/Texture.hpp"

rendering::system::Rendering::Rendering(engine::Registry &registry)
    : _registry(registry)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib background scrolling");

    addSystem<rendering::system::Texture>(
        registry, _registry.get_components<Component::Drawable>(),
        _registry.get_components<Component::Animation>(),
        _registry.get_components<Component::Position>()
    );
    addSystem<rendering::system::Text>(
        _registry.get_components<Component::Text>(),
        _registry.get_components<Component::Position>()
    );
    addSystem<rendering::system::Focusable>(
        _registry.get_components<Component::Focusable>(),
        _registry.get_components<Component::HitBox>(),
        _registry.get_components<Component::Position>()
    );
}

rendering::system::Rendering::~Rendering()
{
    CloseWindow();
}

void rendering::system::Rendering::operator()()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (auto &system : _subSystems)
        (*system)();

    EndDrawing();
}
