/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ShootSoundSystem
*/

#include "ShootSoundSystem.hpp"

System::ShootSoundSystem::ShootSoundSystem(engine::Registry &reg)
    : _register(reg)
{
    _sound = LoadSound(System::SoundManagerSystem::SHOOT_LASER_PATH);
    SetSoundVolume(_sound, 0.1f);
}

bool System::ShootSoundSystem::isAbleToAttack(Component::FireRate &fire_rate)
{
    if (fire_rate.reload_ticks == 0)
        return true;
    return (_register.getTick() % fire_rate.reload_ticks == 0);
}

void System::ShootSoundSystem::operator()()
{
    auto &fireRateList = _register.get_components<Component::FireRate>();

    for (auto it = fireRateList.begin(); it != fireRateList.end(); it++) {
        if (isAbleToAttack(it->value())) {
            PlaySound(_sound);
        }
    }
}
