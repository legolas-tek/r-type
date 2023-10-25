/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** WaveManagerSystem
*/

#include "WaveManagerSystem.hpp"
#include "SoundManagerSystem.hpp"
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
                            .health = 2,
                            .offset = RTypeGame::SHOOT_ENNEMY_W,
                            .frameDuration = 50,
                            .scale = 1.5,
                            .damage = 1,
                            .lifeTime = 200,
                            .fireRate = std::nullopt
                             };
    EntityInfo scourge = { .textureIndex = RTypeGame::BASIC_ENNEMY_I,
                           .textureWidth = RTypeGame::BASIC_ENNEMY_W
                               * RTypeGame::BASIC_ENNEMY_F,
                           .textureHeight = RTypeGame::BASIC_ENNEMY_H,
                           .entityWidth = RTypeGame::BASIC_ENNEMY_W,
                           .entityHeight = RTypeGame::BASIC_ENNEMY_H,
                           .health = 1,
                           .offset = RTypeGame::BASIC_ENNEMY_W,
                           .frameDuration = 50,
                           .scale = 1.5,
                           .damage = 1,
                           .lifeTime = 200,
                           .fireRate = std::nullopt
                           };

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
        if (_waveNum == 2) {
            add_system<System::SpawnEnemySystem>(
                _register, _entityList[1], tick, secondsToTick(1), 832, 832, 40,
                344 - _entityList[1].entityHeight
            );
        }
    }
    run_systems();
}
