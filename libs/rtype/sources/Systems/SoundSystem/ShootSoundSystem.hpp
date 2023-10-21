/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ShootSoundSystem
*/

#ifndef SHOOTSOUNDSYSTEM_HPP_
#define SHOOTSOUNDSYSTEM_HPP_

#include "ISystem.hpp"
#include "Registry.hpp"

#include "Systems/SoundManagerSystem.hpp"

#include "Components/FireRate.hpp"

namespace System {

class ShootSoundSystem : public ISystem {
public:
    ShootSoundSystem(engine::Registry &reg);
    ~ShootSoundSystem() = default;

    void operator()() override;

    bool isAbleToAttack(Component::FireRate &fire_rate);

private:
    engine::Registry &_register;
    Sound _sound;
};
}

#endif /* !SHOOTSOUNDSYSTEM_HPP_ */
