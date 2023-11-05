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
#include "Rendering.hpp"

#include "Components/Collision.hpp"
#include "Components/FireRate.hpp"
#include "Components/Floating.hpp"
#include "Components/Follow.hpp"
#include "Components/Health.hpp"
#include "Components/HitBox.hpp"
#include "Components/Velocity.hpp"
#include "Components/Dependent.hpp"
#include "Components/Damage.hpp"
#include "Components/Solid.hpp"


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
                            .velocity = { -3, 0 },
                            .damage = 2,
                            .lifeTime = 500,
                            .fireRate = 100,
                            .solid = true };
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
                           .velocity = { -10, 0 },
                           .damage = 1,
                           .lifeTime = 300,
                           .fireRate = std::nullopt,
                           .solid = true };

    _entityList.push_back(scourge);
    _entityList.push_back(mutalisk);
}

void System::WaveManagerSystem::createBoss()
{
    engine::Entity bossBody(_register.get_new_entity());
    engine::Entity firstTurret(_register.get_new_entity());
    engine::Entity secondTurret(_register.get_new_entity());
    engine::Entity bossHead(_register.get_new_entity());

    _register.get_components<Component::Position>().emplace_at(
        bossBody, rendering::system::SCREEN_WIDTH + 300, 0, 0
    );
    _register.get_components<Component::Drawable>().emplace_at(
        bossBody, RTypeGame::FIRST_BOSS_I, RTypeGame::FIRST_BOSS_W,
        RTypeGame::FIRST_BOSS_H
    );
    _register.get_components<Component::Animation>().emplace_at(
        bossBody, RTypeGame::FIRST_BOSS_W * RTypeGame::FIRST_BOSS_F,
        RTypeGame::FIRST_BOSS_H, RTypeGame::FIRST_BOSS_W,
        RTypeGame::FIRST_BOSS_H, RTypeGame::FIRST_BOSS_W, 20
    );
    _register.get_components<Component::Floating>().emplace_at(
        bossBody,
        rendering::system::SCREEN_HEIGHT - RTypeGame::BORDERS_H / 2
            - RTypeGame::FIRST_BOSS_H / 2,
        rendering::system::SCREEN_WIDTH - RTypeGame::FIRST_BOSS_W / 2,
        0 + RTypeGame::BORDERS_H / 2 + RTypeGame::FIRST_BOSS_H / 2,
        0 + RTypeGame::FIRST_BOSS_W + RTypeGame::SHIP_W * 3, 3
    );
    _register.get_components<Component::Velocity>().emplace_at(bossBody, 0, 0);
    _register.get_components<Component::Position>().emplace_at(
        firstTurret, 0, 1
    );
    _register.get_components<Component::Drawable>().emplace_at(
        firstTurret, RTypeGame::SMALL_TURRET_I, RTypeGame::SMALL_TURRET_W,
        RTypeGame::SMALL_TURRET_H
    );
    _register.get_components<Component::Follow>().emplace_at(
        firstTurret, bossBody, 7, 2
    );
    _register.get_components<Component::FireRate>().emplace_at(firstTurret, 75);
    _register.get_components<Component::Position>().emplace_at(
        secondTurret, 0, 1
    );
    _register.get_components<Component::Drawable>().emplace_at(
        secondTurret, RTypeGame::SMALL_TURRET_I, RTypeGame::SMALL_TURRET_W,
        RTypeGame::SMALL_TURRET_H
    );
    _register.get_components<Component::Follow>().emplace_at(
        secondTurret, bossBody, 7, 2 + RTypeGame::SMALL_TURRET_H
    );
    _register.get_components<Component::FireRate>().emplace_at(
        secondTurret, 75
    );
    _register.get_components<Component::Position>().emplace_at(bossHead, 0, 0);
    _register.get_components<Component::Follow>().emplace_at(
        bossHead, bossBody, 0, -80
    );
    _register.get_components<Component::Collision>().emplace_at(
        bossHead, 113, 83
    );
    _register.get_components<Component::Damage>().emplace_at(bossHead, 3);
    _register.get_components<Component::Solid>().emplace_at(bossHead);
    _register.get_components<Component::HitBox>().emplace_at(bossHead, 113, 83);
    _register.get_components<Component::Health>().emplace_at(bossHead, 10, 10);
    _register.get_components<Component::Dependent>().emplace_at(
        bossBody, bossHead
    );
    _register.get_components<Component::Dependent>().emplace_at(
        firstTurret, bossHead
    );
    _register.get_components<Component::Dependent>().emplace_at(
        secondTurret, bossHead
    );
    _register.get_components<Component::Health>().emplace_at(bossBody, 10, 10);
    _register.get_components<Component::Health>().emplace_at(
        firstTurret, 10, 10
    );
    _register.get_components<Component::Health>().emplace_at(
        secondTurret, 10, 10
    );
}

void System::WaveManagerSystem::operator()()
{
    size_t tick = _register.getTick();
    size_t maxWave = WAVE_START_TICK_TABLE.size();

    if (_waveNum < maxWave and tick == WAVE_START_TICK_TABLE[_waveNum]) {
        _waveNum++;
        if (_waveNum == 1) {
            add_system<System::SpawnEnemySystem>(
                _register, _entityList[0], tick, secondsToTick(1),
                rendering::system::SCREEN_WIDTH + _entityList[0].entityWidth,
                rendering::system::SCREEN_WIDTH + _entityList[0].entityWidth,
                RTypeGame::BORDERS_H + _entityList[0].entityHeight / 2,
                rendering::system::SCREEN_HEIGHT - _entityList[0].entityHeight /
                    2 - RTypeGame::BORDERS_H
            );
        }
        if (_waveNum == 2) {
            _systems.clear();
            add_system<System::SpawnEnemySystem>(
                _register, _entityList[1], tick, secondsToTick(1),
                rendering::system::SCREEN_WIDTH + _entityList[1].entityWidth,
                rendering::system::SCREEN_WIDTH + _entityList[1].entityWidth,
                RTypeGame::BORDERS_H + _entityList[1].entityHeight / 2,
                rendering::system::SCREEN_HEIGHT - _entityList[1].entityHeight /
                    2 - RTypeGame::BORDERS_H
            );
        }
        if (_waveNum == 3) {
            _systems.clear();
            createBoss();
        }
    }
    run_systems();
}
