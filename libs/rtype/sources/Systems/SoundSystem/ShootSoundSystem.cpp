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
}

void System::ShootSoundSystem::operator()()
{
    std::cout << "shoot system" << std::endl;
}
