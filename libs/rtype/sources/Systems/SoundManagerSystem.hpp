/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** SoundManagerSystem
*/

#ifndef SOUNDMANAGERSYSTEM_HPP_
#define SOUNDMANAGERSYSTEM_HPP_

#include "ISystem.hpp"
#include "Registry.hpp"

#include <raylib.h>

// TODO: docu => avant Dead et apres Damage
namespace System {

class SoundManagerSystem : public ISystem {
public:
    static inline constexpr char *WAVE1_MUSIC_PATH
        = "./assets/sounds/wave1.mp3";
    static inline constexpr char *SHOOT_LASER_PATH
        = "./assets/sounds/shootLaser.mp3";
    static inline constexpr char *EXPLOSION_PATH
        = "./assets/sounds/explosion.mp3";
    static inline constexpr char *WAVE2_PATH = "./assets/sounds/wave2.mp3";

public:
    SoundManagerSystem(engine::Registry &reg);
    ~SoundManagerSystem();

    void operator()() override;

    void changeMusic(char const *soundPath);

    template <typename System, class... Params>
    ISystem &add_system(Params &&...args)
    {
        return *_systems.emplace_back(
            std::make_unique<System>(std::forward<Params>(args)...)
        );
    }

    void run_systems()
    {
        for (auto &system : _systems)
            (*system)();
    }

private:
    engine::Registry &_register;
    Music _music;

    std::vector<std::unique_ptr<ISystem>> _systems;
};
}
#endif /* !SOUNDMANAGERSYSTEM_HPP_ */
