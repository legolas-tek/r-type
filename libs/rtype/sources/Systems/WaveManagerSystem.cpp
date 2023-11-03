/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** WaveManagerSystem
*/

#include "WaveManagerSystem.hpp"
#include "SoundManagerSystem.hpp"
#include "SpawnEnemySystem.hpp"

#include "Rendering.hpp"

#include "Game.hpp"
#include <iostream>

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
                            .velocity = {-3, 0},
                            .damage = 1,
                            .lifeTime = 200,
                            .fireRate = 100
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
                           .velocity = {-10, 0},
                           .damage = 1,
                           .lifeTime = 200,
                           .fireRate = std::nullopt
                           };

    _entityList.push_back(scourge);
    _entityList.push_back(mutalisk);
}

void System::WaveManagerSystem::createBoss()
{
    engine::Entity boss(_register.get_new_entity());

    _register.get_components<Component::Position>().emplace_at(
        boss, rendering::system::SCREEN_WIDTH + 300, 0, 0
    );
    _register.get_components<Component::Drawable>().emplace_at(
        boss, RTypeGame::FIRST_BOSS_I, RTypeGame::FIRST_BOSS_W, RTypeGame::FIRST_BOSS_H, 1.5
    );
}

void System::WaveManagerSystem::operator()()
{
    size_t tick = _register.getTick();
    size_t maxWave = WAVE_START_TICK_TABLE.size();

    // if (_waveNum == maxWave) {
    //     return;
    // }
    if (tick == WAVE_START_TICK_TABLE[_waveNum]) {
        _waveNum++;
        std::cout << "next wave" << std::endl;
        if (_waveNum == 1) {
            add_system<System::SpawnEnemySystem>(
                _register, _entityList[0], tick, secondsToTick(1), 832, 832, 40,
                344 - _entityList[0].entityHeight
            );
        }
        if (_waveNum == 2) {
            _systems.clear();
            add_system<System::SpawnEnemySystem>(
                _register, _entityList[1], tick, secondsToTick(1), 832, 832, 40,
                344 - _entityList[1].entityHeight
            );
        }
        if (_waveNum == 3) {
            _systems.clear();
            createBoss();
        }
    }
    run_systems();
}
