/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** SoundManagerSystem
*/

#include "SoundManagerSystem.hpp"

System::SoundManagerSystem::SoundManagerSystem(
    engine::Registry &reg, size_t soundPathIndex
)
    : _register(reg)
{
    InitAudioDevice();
    _music = LoadMusicStream(_register._sounds_paths[0].c_str());
    _music.looping = true;

    PlayMusicStream(_music);
}

System::SoundManagerSystem::~SoundManagerSystem()
{
}

void System::SoundManagerSystem::operator()()
{
    UpdateMusicStream(_music);
}