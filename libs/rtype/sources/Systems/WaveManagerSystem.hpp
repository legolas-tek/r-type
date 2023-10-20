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

static inline constexpr size_t seconds_to_tick(float sec)
{
    return 60 * sec + 1;
}

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

    // better to have a multiple of 4 sec (4 % 0.016 = 0)
    static inline constexpr std::array<size_t, 3> WAVE_START_SEC_TABLE = {
        seconds_to_tick(0), // wave 1 start sec
        seconds_to_tick(4), // wave 1 start sec
        seconds_to_tick(8) // wave 1 start sec
    };

    static inline constexpr std::array<size_t, 2> WAVE_PADDING
        = { seconds_to_tick(0.4), seconds_to_tick(0.4) };
};
}
#endif /* !WAVEMANAGERSYSTEM_HPP_ */
