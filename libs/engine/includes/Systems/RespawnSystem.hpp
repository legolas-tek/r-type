/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** LifeSystems
*/

#ifndef RESPAWNSYSTEM_HPP_
#define RESPAWNSYSTEM_HPP_

#include "ISystem.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"

#include "Components/Collision.hpp"
#include "Components/Controllable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Health.hpp"
#include "Components/HitBox.hpp"
#include "Components/Life.hpp"
#include "Components/Velocity.hpp"

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
        SparseArray<Component::Controllable> &controllables,
        SparseArray<Component::Drawable> &drawables,
        SparseArray<Component::Velocity> &velocities,
        SparseArray<Component::Collision> &collisions,
        SparseArray<Component::HitBox> &hitboxes, engine::Registry &reg,
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

    /// @brief An unordered map that stores the ticks at wich the entitys
    /// should respawn
    std::unordered_map<size_t, size_t> _respawnsTicks;
    /// @brief An unordered map that stores copys of the Drawable components
    /// that we delete from our respawning entities
    std::unordered_map<size_t, Component::Drawable> _drawableComps;
    /// @brief An unordered map that stores copys of the Collision components
    /// that we delete from our respawning entities
    std::unordered_map<size_t, Component::Collision> _collisionComps;
    /// @brief An unordered map that stores copys of the Controllable components
    /// that we delete from our respawning entities
    std::unordered_map<size_t, Component::Controllable> _controllableComps;
    /// @brief An unordered map that stores copys of the Controllable components
    /// that we delete from our respawning entities
    std::unordered_map<size_t, Component::HitBox> _hitboxComps;
    /// @brief A reference to a Life components SparseArray
    SparseArray<Component::Life> &_lifes;
    /// @brief A reference to a Health components SparseArray
    SparseArray<Component::Health> &_healths;
    /// @brief A reference to a Controllable components SparseArray
    SparseArray<Component::Controllable> &_controllables;
    /// @brief A reference to a Drawable components SparseArray
    SparseArray<Component::Drawable> &_drawables;
    /// @brief A reference to a Velocity components SparseArray
    SparseArray<Component::Velocity> &_velocities;
    /// @brief A reference to a Collision components SparseArray
    SparseArray<Component::Collision> &_collisions;
    /// @brief A reference to a HitBox components SparseArray
    SparseArray<Component::HitBox> &_hitboxes;
    /// @brief a reference to the registry
    engine::Registry &_reg;
    /// @brief The ticks it takes for a unit to respawn
    int _respawnCooldown = 150;
};

}
#endif /* !RESPAWNSYSTEM_HPP_ */
