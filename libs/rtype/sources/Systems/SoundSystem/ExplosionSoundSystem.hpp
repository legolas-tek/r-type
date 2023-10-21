/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ExplosionSoundSystem
*/

#ifndef EXPLOSIONSOUNDSYSTEM_HPP_
#define EXPLOSIONSOUNDSYSTEM_HPP_

#include <iostream>

#include "ISystem.hpp"
#include "Registry.hpp"

#include "Components/Life.hpp"

#include "Systems/SoundManagerSystem.hpp"

namespace System {
class ExplosionSoundSystem : public ISystem {
public:
    ExplosionSoundSystem(engine::Registry &reg);
    ~ExplosionSoundSystem() = default;

    void operator()() override;

private:
    engine::Registry &_register;
    Sound _sound;
};
}

#endif /* !EXPLOSIONSOUNDSYSTEM_HPP_ */
