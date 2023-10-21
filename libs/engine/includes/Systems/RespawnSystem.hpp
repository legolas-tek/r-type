/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** LifeSystems
*/

#ifndef RESPAWNSYSTEM_HPP_
#define RESPAWNSYSTEM_HPP_

#include "ISystem.hpp"
#include "SparseArray.hpp"
#include "Registry.hpp"

#include "Components/Life.hpp"
#include "Components/Health.hpp"
#include "Components/Drawable.hpp"

namespace System {

/// @brief This system checks all entities who has a Life component to respawn
/// them if they have 0 health and enough lifes. This system should always be
/// used with the death system to fonction properly
class RespawnSystem : public ISystem {
public:
    /// @brief Construct an instance of a RespawnSystem class
    /// @param life_times_ref A ref to a Life components SparseArray
    /// @param healths A ref to a Health components SparseArray
    /// @param respawnCooldown The ticks it requires to respawn an entity
    /// @param reg A reference to the registry
    RespawnSystem(
        SparseArray<Component::Life> &lifes,
        SparseArray<Component::Health> &healths,
        engine::Registry &reg,
        int respawnCooldown = 150
    );

    /// @brief Applies the RespawnSystem logic
    void operator()() override;

private:
    /// @brief This method register the tick at wich an entity should respawn
    void registerRespawnEntity(engine::Entity entity);

    /// @brief This method respawns the given entity
    /// @param entity The entity which should be respawned
    void respawnEntity(size_t entity);

    int _respawnCooldown = 150;
    /// @brief An unordered map that stores the ticks at wich the entitys
    /// should respawn
    std::unordered_map<size_t, size_t> _respawnsTicks;
    /// @brief An unordered map that stores copys of the drawables components
    /// that we delete from our respawning entities
    std::unordered_map<size_t, Component::Drawable> _drawableComps;
    /// @brief A reference to a Life components SparseArray
    SparseArray<Component::Life> &_lifes;
    /// @brief A reference to a Health components SparseArray
    SparseArray<Component::Health> &_healths;
    /// @brief a reference to the registry
    engine::Registry &_reg;
};

}
#endif /* !RESPAWNSYSTEM_HPP_ */
