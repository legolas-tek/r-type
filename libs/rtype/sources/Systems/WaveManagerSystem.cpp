/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** WaveManagerSystem
*/

#include "WaveManagerSystem.hpp"
#include "SpawnEnemySystem.hpp"

System::WaveManagerSystem::WaveManagerSystem(engine::Registry &reg)
    : _register(reg)
{
    EntityInfo mutalisk = { .textureIndex = 5,
                            .textureWidth = 320,
                            .textureHeight = 72,
                            .entityWidth = 64,
                            .entityHeight = 72,
                            .offset = 64,
                            .frameDuration = 10,
                            .scale = 2.0f,
                            .damage = std::nullopt,
                            .lifeTime = std::nullopt,
                            .fireRate = std::nullopt };
    EntityInfo scourge = { .textureIndex = 6,
                           .textureWidth = 155,
                           .textureHeight = 27,
                           .entityWidth = 31,
                           .entityHeight = 27,
                           .offset = 31,
                           .frameDuration = 10,
                           .scale = 2.0f,
                           .damage = std::nullopt,
                           .lifeTime = std::nullopt,
                           .fireRate = std::nullopt };

    _entityList.push_back(mutalisk);
    _entityList.push_back(scourge);
}

void System::WaveManagerSystem::operator()()
{
    size_t tick = _register.getTick();
    size_t maxWave = WAVE_START_TICK_TABLE.size();

    if (_waveNum == maxWave) {
        return;
    }
    if (tick == WAVE_START_TICK_TABLE[_waveNum]) {
        _waveNum++;
        if (_waveNum == 1) {
            add_system<System::SpawnEnemySystem>(
                _register, _entityList[0], tick, secondsToTick(1), 700, 700, 0,
                450 - int(_entityList[0].entityHeight)
            );
        }
        if (_waveNum == 2) { }
    }
    run_systems();
}
