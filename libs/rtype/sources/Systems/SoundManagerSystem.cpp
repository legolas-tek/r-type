/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** SoundManagerSystem
*/

#include "SoundManagerSystem.hpp"
#include "SoundSystem/ExplosionSoundSystem.hpp"
#include "SoundSystem/ShootSoundSystem.hpp"

System::SoundManagerSystem::SoundManagerSystem(engine::Registry &reg)
    : _register(reg)
{
    InitAudioDevice();
    _music = LoadMusicStream(WAVE1_MUSIC_PATH);
    _music.looping = true;

    SetMusicVolume(_music, 0.1f);
    PlayMusicStream(_music);

    add_system<System::ShootSoundSystem>(_register);
    add_system<System::ExplosionSoundSystem>(_register);
}

System::SoundManagerSystem::~SoundManagerSystem()
{
    UnloadMusicStream(_music);
    CloseAudioDevice();
}

void System::SoundManagerSystem::operator()()
{
    UpdateMusicStream(_music);
    run_systems();
}

void System::SoundManagerSystem::changeMusic(char const *soundPath)
{
    _music = LoadMusicStream(soundPath);
    _music.looping = true;

    PlayMusicStream(_music);
}
