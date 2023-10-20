/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** SpawnEnemySystem
*/

#include "SpawnEnemySystem.hpp"

#include "Rendering.hpp"

System::SpawnEnemySystem::SpawnEnemySystem(engine::Registry &reg)
    : _register(reg)
{
    EntityInfo mutalisk = { 5, 320, 72, 64, 72, 64, 10, 0, 0, 2.0f };
    EntityInfo scourge = { 6, 155, 27, 31, 27, 31, 10, 0, 0, 2.0f };

    _entityList.push_back(mutalisk);
    _entityList.push_back(scourge);
}

static void addEntity(engine::Registry &reg, EntityInfo entityInfo)
{
    engine::Entity enemy(reg.get_new_entity());
    int randomY = std::rand()
        % static_cast<int>(
                      rendering::system::SCREEN_HEIGHT - entityInfo.entityHeight
        );

    // set position
    reg.get_components<Component::Position>().insert_at(
        enemy, std::move(Component::Position(700, randomY, 0))
    );
    // set Drawable
    reg.get_components<Component::Drawable>().insert_at(
        enemy,
        std::move(Component::Drawable(
            entityInfo.textureIndex, entityInfo.entityWidth,
            entityInfo.entityHeight, entityInfo.scale
        ))
    );
    // set Animation
    reg.get_components<Component::Animation>().insert_at(
        enemy,
        std::move(Component::Animation(
            entityInfo.textureWidth, entityInfo.textureHeight,
            entityInfo.entityWidth, entityInfo.entityHeight, entityInfo.offset,
            entityInfo.frameDuration
        ))
    );
}

void System::SpawnEnemySystem::addEnemy()
{
    int randomValue = (std::rand() % 2);

    addEntity(_register, _entityList[randomValue]);
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
            std::cout << "created in wave " << _waveNum << " tick " << tick
                      << std::endl;
            addEnemy();
            _createdNum++;
        }
    }
}
