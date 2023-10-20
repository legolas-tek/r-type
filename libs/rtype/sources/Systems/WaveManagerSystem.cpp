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
    EntityInfo mutalisk = { 5, 320, 72, 64, 72, 64, 10, 2.0f };
    EntityInfo scourge = { 6, 155, 27, 31, 27, 31, 10, 2.0f };

    _entityList.push_back(mutalisk);
    _entityList.push_back(scourge);
}

void System::WaveManagerSystem::operator()()
{
    size_t tick = _register.getTick();
    size_t maxWave
        = sizeof(WAVE_START_SEC_TABLE) / sizeof(WAVE_START_SEC_TABLE[0]);

    if (_waveNum == maxWave) {
        std::cout << "end wave" << std::endl;
        return;
    }
    if (tick == WAVE_START_SEC_TABLE[_waveNum]) {
        std::cout << "wave " << _waveNum << " to " << _waveNum + 1 << std::endl;
        _waveNum++;
        if (_waveNum == 1) {
            add_system<System::SpawnEnemySystem>(
                _register, _entityList[0], tick, seconds_to_tick(1), 700, 700,
                0, 450 - _entityList[0].entityHeight
            );

            std::cout << "Wave 1" << std::endl;
        }
        if (_waveNum == 2) {
            std::cout << "Wave 2" << std::endl;
        }
    }
    run_systems();
}
