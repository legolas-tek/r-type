
/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Rendering
*/

#include <raylib.h>

#include "Rendering.hpp"

rendering::Rendering::Rendering(engine::Registry &registry)
: _registry(registry)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib background scrolling");
}

rendering::Rendering::~Rendering()
{
    CloseWindow();
}
