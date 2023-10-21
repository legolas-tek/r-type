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

#include <iostream>

namespace System {
class SoundManagerSystem : public ISystem {
public:
    SoundManagerSystem(engine::Registry &reg, size_t soundPathIndex);
    ~SoundManagerSystem();

    void operator()() override;

private:
    engine::Registry &_register;
    Music _music;
};
}
#endif /* !SOUNDMANAGERSYSTEM_HPP_ */
