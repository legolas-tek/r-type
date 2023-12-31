
/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Rendering
*/

#include "Rendering.hpp"

#include "Systems/Close.hpp"
#include "Systems/Mouse.hpp"
#include "Systems/Text.hpp"
#include "Systems/Texture.hpp"

rendering::system::Rendering::Rendering(engine::Registry &registry)
    : _registry(registry)
{
    SetTraceLogLevel(LOG_NONE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib background scrolling");

    CameraInfo cameraInfo = { .pos = { 0.0f, 0.0f, 50.0f },
                              .target = { 0.0f, 0.0f, 0.0f },
                              .up = { 0.0f, 1.0f, 0.0f },
                              .fovy = 45.0f,
                              .projection = CAMERA_PERSPECTIVE };
    addSystem<rendering::system::Texture>(
        registry, _registry.get_components<Component::Drawable>(),
        _registry.get_components<Component::Animation>(),
        _registry.get_components<Component::Position>(), cameraInfo
    );
    addSystem<rendering::system::Text>(
        _registry.get_components<Component::Text>(),
        _registry.get_components<Component::Position>()
    );
    addSystem<rendering::system::Mouse>(_registry.events);
    addSystem<rendering::system::Close>(_registry.events);
}

rendering::system::Rendering::~Rendering()
{
    CloseWindow();
}

void rendering::system::Rendering::operator()()
{
    if (WindowShouldClose()) {
        _registry.events.addEvent<event::Close>();
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (auto &system : _subSystems)
        (*system)();

    EndDrawing();
}
