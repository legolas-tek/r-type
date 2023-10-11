/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameLoop
*/

#include <iostream>
#include <chrono>

#include "Registry.hpp"

void gameLoop(engine::Registry &reg)
{
    auto previous_time = std::chrono::high_resolution_clock::now();
    float target_delta_time = 1.0f / 60.0f;
    float elapsed_time = 0.0f;

    while (1) {
        auto current_time = std::chrono::high_resolution_clock::now();
        auto time_difference = current_time - previous_time;
        previous_time = current_time;

        float delta_time = std::chrono::duration<float>(time_difference).count();
        elapsed_time += delta_time;

        if (elapsed_time >= target_delta_time) {
            reg.run_systems();
            elapsed_time = 0.0f;
        }
    }
}
