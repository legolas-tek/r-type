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

#include <iostream>

namespace System {

class ShootSoundSystem : public ISystem {
public:
    ShootSoundSystem(engine::Registry &reg);
    ~ShootSoundSystem() = default;

    void operator()() override;

private:
    engine::Registry &_register;
};
}

#endif /* !SHOOTSOUNDSYSTEM_HPP_ */
