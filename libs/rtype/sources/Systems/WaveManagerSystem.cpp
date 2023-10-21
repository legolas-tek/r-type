/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** WaveManagerSystem
*/

#include "WaveManagerSystem.hpp"
#include "SpawnEnemySystem.hpp"

#include "Game.hpp"

System::WaveManagerSystem::WaveManagerSystem(engine::Registry &reg)
    : _register(reg)
{
    EntityInfo mutalisk = { .textureIndex = RTypeGame::SHOOT_ENNEMY_I,
                            .textureWidth = RTypeGame::SHOOT_ENNEMY_W
                                * RTypeGame::SHOOT_ENNEMY_F,
                            .textureHeight = RTypeGame::SHOOT_ENNEMY_H,
                            .entityWidth = RTypeGame::SHOOT_ENNEMY_W,
                            .entityHeight = RTypeGame::SHOOT_ENNEMY_H,
                            .offset = RTypeGame::SHOOT_ENNEMY_W,
                            .frameDuration = 50,
                            .scale = 1.5 };
    EntityInfo scourge = { .textureIndex = RTypeGame::BASIC_ENNEMY_I,
                           .textureWidth = RTypeGame::BASIC_ENNEMY_W
                               * RTypeGame::BASIC_ENNEMY_F,
                           .textureHeight = RTypeGame::BASIC_ENNEMY_H,
                           .entityWidth = RTypeGame::BASIC_ENNEMY_W,
                           .entityHeight = RTypeGame::BASIC_ENNEMY_H,
                           .offset = RTypeGame::BASIC_ENNEMY_W,
                           .frameDuration = 50,
                           .scale = 1.5 };

    _entityList.push_back(scourge);
    _entityList.push_back(mutalisk);
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
                _register, _entityList[0], tick, secondsToTick(1), 832, 832, 40,
                344 - _entityList[0].entityHeight
            );
        }
        if (_waveNum == 2) { }
    }
    run_systems();
}
