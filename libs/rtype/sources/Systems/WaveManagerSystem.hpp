/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** WaveManagerSystem
*/

#ifndef WAVEMANAGERSYSTEM_HPP_
#define WAVEMANAGERSYSTEM_HPP_

#include <array>

#include "ISystem.hpp"
#include "Registry.hpp"

#include "EntityInfo.hpp"

namespace System {

static inline constexpr size_t secondsToTick(float sec)
{
    return static_cast<size_t>(60 * sec + 1);
}

class WaveManagerSystem : public ISystem {
public:
    explicit WaveManagerSystem(engine::Registry &reg);
    ~WaveManagerSystem() override = default;

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

    // better to have a multiple of 4 sec (4 % 0.016 = 0)
    static inline constexpr std::array<size_t, 3> WAVE_START_TICK_TABLE = {
        secondsToTick(0), // wave 1 start sec
        secondsToTick(30), // wave 2 start sec
        secondsToTick(60) // wave 3 start sec
    };
};
}
#endif /* !WAVEMANAGERSYSTEM_HPP_ */
