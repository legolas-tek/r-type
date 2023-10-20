/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** WaveManagerSystem
*/

#ifndef WAVEMANAGERSYSTEM_HPP_
#define WAVEMANAGERSYSTEM_HPP_

#include "ISystem.hpp"
#include "Registry.hpp"

#include <iostream>

#include "EntityInfo.hpp"

namespace System {

static inline constexpr size_t seconds_to_tick(float sec)
{
    return 60 * sec + 1;
}

// better to have a multiple of 4 sec (4 % 0.016 = 0)
size_t constexpr WAVE_START_SEC_TABLE[] = {
    seconds_to_tick(0), // wave 1 start sec
    seconds_to_tick(4), // wave 1 start sec
    seconds_to_tick(8) // wave 1 start sec
};

size_t constexpr WAVE_PADDING[]
    = { seconds_to_tick(0.4), seconds_to_tick(0.4) };

class WaveManagerSystem : public ISystem {
public:
    WaveManagerSystem(engine::Registry &reg);
    ~WaveManagerSystem() = default;

    void operator()() override;

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

protected:
private:
    engine::Registry &_register;
    size_t _waveNum = 0;
    std::vector<std::unique_ptr<ISystem>> _systems;
    std::vector<EntityInfo> _entityList;
};
}
#endif /* !WAVEMANAGERSYSTEM_HPP_ */
