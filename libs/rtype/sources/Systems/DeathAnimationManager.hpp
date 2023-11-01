/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DeathAnimationManager
*/

#ifndef DEATHANIMATIONMANAGER_HPP_
#define DEATHANIMATIONMANAGER_HPP_

#include "ISystem.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"

#include "Components/Collision.hpp"
#include "Components/Damage.hpp"
#include "Components/Health.hpp"
#include "Components/Position.hpp"
#include "Components/Controllable.hpp"

namespace System {

/// @brief This system allows entities with the component life set to 0 to have
/// a death animation !!!!!! This system should always be registered before the
/// death system if you use both of them !!!!!!
class DeathAnimationManager : public ISystem {
    /// @brief The width of the explosion sprite
    static inline constexpr int EXPLOSION_WIDTH = 15;
    /// @brief The height of the explosion sprite
    static inline constexpr int EXPLOSION_HEIGHT = 14;
    /// @brief The index to find the explosion sprite
    static inline constexpr int EXPLOSION_INDEX = 5;
    /// @brief The number of frames for the explosion animation
    static inline constexpr int EXPLOSION_FRAMES = 6;

    /// @brief The width of the big explosion sprite
    static inline constexpr int BIG_EX_WIDTH = 32;
    /// @brief The height of the big explosion sprite
    static inline constexpr int BIG_EX_HEIGHT = 31;
    /// @brief The index to find the big explosion sprite
    static inline constexpr int BIG_EX_INDEX = 10;
    /// @brief The number of frames for the big explosion animation
    static inline constexpr int BIG_EX_FRAMES = 6;

public:
    /// @brief constructs an instance of a DeathAnimation System class
    /// @param healths A ref to a Health components SparseArray
    /// @param reg A ref to the registry
    DeathAnimationManager(
        SparseArray<Component::Position> &positions,
        SparseArray<Component::Health> &healths,
        SparseArray<Component::Collision> &collisions,
        SparseArray<Component::Damage> &damages,
        SparseArray<Component::Controllable> &controllables,
        engine::Registry &reg
    );

    /// @brief applys the system logic
    void operator()() override;

private:
    /// @brief creates an explosion entity that represents the impact
    /// of the laser
    /// @param pos The position of the explosion
    void createExplosion(Component::Position const &pos);

    /// @brief creates an explosion entity that represents another entity
    /// exploding
    /// @param pos The position of the explosion
    void createBigExplosion(Component::Position pos);

    /// @brief A ref to a Position components SparseArray
    SparseArray<Component::Position> &_positions;
    /// @brief A ref to a Damage components SparseArray
    SparseArray<Component::Damage> &_damages;
    /// @brief A ref to a Health components SparseArray
    SparseArray<Component::Health> &_healths;
    /// @brief A ref to a Hitbox components SparseArray
    SparseArray<Component::Collision> &_collisions;
    /// @brief A ref to a Controllable components SparseArray
    SparseArray<Component::Controllable> &_controllables;
    /// @brief A ref to the registry
    engine::Registry &_registry;
};

}
#endif /* !DEATHANIMATIONMANAGER_HPP_ */
