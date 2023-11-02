/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ExplosionSoundSystem
*/

#include "ExplosionSoundSystem.hpp"

System::ExplosionSoundSystem::ExplosionSoundSystem(engine::Registry &reg)
    : _register(reg)
{
    _sound = LoadSound(System::SoundManagerSystem::EXPLOSION_PATH);
    SetSoundVolume(_sound, 0.1f);
}

void System::ExplosionSoundSystem::operator()()
{
    auto &lifeList = _register.get_components<Component::Health>();

    for (auto it = lifeList.begin(); it != lifeList.end(); it++) {
        if ((*it)->health <= 0)
            PlaySound(_sound);
    }
}
