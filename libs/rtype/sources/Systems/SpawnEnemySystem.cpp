/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** SpawnEnemySystem
*/

#include "SpawnEnemySystem.hpp"

System::SpawnEnemySystem::SpawnEnemySystem(engine::Registry &reg)
    : _register(reg)
{
}

static float tickToSecond(size_t tick)
{
    return tick * 0.016;
}

void System::SpawnEnemySystem::operator()()
{
    float second = tickToSecond(_register.getTick());

    std::cout << "=========================" << std::endl;
    std::cout << "second " << second << std::endl;

    if (WAVE_1_START_SEC <= second && second <= WAVE_2_START_SEC) {
        std::cout << "wave 1" << std::endl;
        if (WAVE_1_START_SEC + WAVE_1_PADDING_SPAWN <= second
            && second <= WAVE_2_START_SEC - WAVE_1_PADDING_SPAWN) {
            std::cout << "can spawn for "
                      << WAVE_2_START_SEC - WAVE_1_START_SEC
                    - (WAVE_1_PADDING_SPAWN * 2)
                      << std::endl;
        }
    }
    if (WAVE_2_START_SEC <= second) {
        std::cout << "wave 2" << std::endl;
    }
}
