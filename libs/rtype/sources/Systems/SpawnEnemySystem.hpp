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

namespace System {

// better to have a multiple of 4 sec (4 % 0.016 = 0)
float const WAVE_1_START_SEC = 0.0f;
float const WAVE_2_START_SEC = 4.0f;

float const WAVE_1_PADDING_SPAWN = 0.4;

int const WAVE_1_ENEMY_NUM = 2;

class SpawnEnemySystem : public ISystem {
public:
    SpawnEnemySystem(engine::Registry &reg);
    ~SpawnEnemySystem() = default;

    void operator()() override;

private:
    engine::Registry &_register;
};
}

#endif /* !SPAWNENEMYSYSTEM_HPP_ */
