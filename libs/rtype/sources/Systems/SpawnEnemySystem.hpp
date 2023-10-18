/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** SpawnEnemySystem
*/

#ifndef SPAWNENEMYSYSTEM_HPP_
#define SPAWNENEMYSYSTEM_HPP_

#include "Registry.hpp"

#include "ISystem.hpp"

#include <iostream>

#include "Components/Animation.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"

namespace System {

static inline constexpr size_t seconds_to_tick(float sec)
{
    return 60 * sec;
}

// better to have a multiple of 4 sec (4 % 0.016 = 0)
size_t constexpr WAVE_START_SEC_TABLE[] = {
    seconds_to_tick(0), // wave 1 start sec
    seconds_to_tick(4), // wave 1 start sec
    seconds_to_tick(8) // wave 1 start sec
};

size_t constexpr WAVE_PADDING[]
    = { seconds_to_tick(0.4), seconds_to_tick(0.4) };

size_t constexpr WAVE_ENEMY_NUM[] = {
    3, // spawn 2 enemy in wave 0
    3 // spawn 1 enemy in wave 0
};

float const WAVE_1_PADDING_SPAWN = 0.4;

int const WAVE_1_ENEMY_NUM = 2;

class SpawnEnemySystem : public ISystem {
public:
    SpawnEnemySystem(engine::Registry &reg);
    ~SpawnEnemySystem() = default;

    void operator()() override;

private:
    engine::Registry &_register;
    size_t _waveNum = 0;
    size_t _createdNum = 0;
};
}

#endif /* !SPAWNENEMYSYSTEM_HPP_ */
