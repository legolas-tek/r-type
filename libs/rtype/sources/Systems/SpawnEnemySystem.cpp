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

static void addEnemy1(engine::Registry &reg)
{
    engine::Entity enemy(10);

    // set position
    reg.get_components<Component::Position>().insert_at(
        enemy, std::move(Component::Position(300, 100, 0))
    );
    // set Drawable
    reg.get_components<Component::Drawable>().insert_at(
        enemy, std::move(Component::Drawable(6, 31.0f, 27.0f, 2.0f))
    );
    // set Animation
    reg.get_components<Component::Animation>().insert_at(
        enemy, std::move(Component::Animation(155, 27, 31, 27, 31, 10))
    );
}

static void addEnemy2(engine::Registry &reg)
{
    engine::Entity enemy(11);

    // set position
    reg.get_components<Component::Position>().insert_at(
        enemy, std::move(Component::Position(400, 100, 0))
    );
    // set Drawable
    reg.get_components<Component::Drawable>().insert_at(
        enemy, std::move(Component::Drawable(5, 64.0f, 72.0f, 2.0f))
    );
    // set Animation
    reg.get_components<Component::Animation>().insert_at(
        enemy, std::move(Component::Animation(320, 72, 64, 72, 64, 10))
    );
}

static void addEnemy(engine::Registry &reg)
{
    int randomValue = std::rand() % 2;

    if (randomValue == 1) {
        addEnemy1(reg);
    } else {
        addEnemy2(reg);
    }
}

void System::SpawnEnemySystem::operator()()
{
    size_t tick = _register.getTick();
    size_t maxWave
        = sizeof(WAVE_START_SEC_TABLE) / sizeof(WAVE_START_SEC_TABLE[0]);

    if (_waveNum == maxWave - 1) {
        std::cout << "end" << std::endl;
        return;
    }

    if (tick == WAVE_START_SEC_TABLE[_waveNum + 1]) {
        std::cout << "wave " << _waveNum << " to " << _waveNum + 1 << std::endl;
        _waveNum++;
    }

    size_t start_create_tick
        = WAVE_START_SEC_TABLE[_waveNum] + WAVE_PADDING[_waveNum];
    size_t end_create_tick
        = WAVE_START_SEC_TABLE[_waveNum + 1] - WAVE_PADDING[_waveNum];

    if (start_create_tick <= tick && tick <= end_create_tick) {
        size_t random = std::rand() % (end_create_tick - start_create_tick);
        bool isInPercent = random < WAVE_ENEMY_NUM[_waveNum];

        if (isInPercent) {
            std::cout << "created in wave " << _waveNum << std::endl;
            addEnemy(_register);
            _createdNum++;
        }
    }
}
