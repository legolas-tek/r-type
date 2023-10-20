/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DamageSystem
*/

#ifndef DAMAGESYSTEM_HPP_
#define DAMAGESYSTEM_HPP_

#include "ISystem.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"

#include "Components/Collision.hpp"
#include "Components/Damage.hpp"
#include "Components/Life.hpp"
#include "Components/Position.hpp"

/// @brief The width of the explosion sprite
inline constexpr int EXPLOSION_WIDTH = 15;
/// @brief The height of the explosion sprite
inline constexpr int EXPLOSION_HEIGHT = 14;
/// @brief The index to find the explosion sprite
inline constexpr int EXPLOSION_INDEX = 5;
/// @brief The number of frames for the explosion animation
inline constexpr int EXPLOSION_FRAMES = 6;

/// @brief The width of the big explosion sprite
inline constexpr int BIG_EX_WIDTH = 32;
/// @brief The height of the big explosion sprite
inline constexpr int BIG_EX_HEIGHT = 31;
/// @brief The index to find the big explosion sprite
inline constexpr int BIG_EX_INDEX = 10;
/// @brief The number of frames for the big explosion animation
inline constexpr int BIG_EX_FRAMES = 6;

namespace System {

/// @brief This system allows entity with the component damage to deal damage
/// on collision to entitys with the component life
class DamageSystem : public ISystem {
public:
    /// @brief constructs an instance of a DamageSystem class
    /// @param damages A ref to a Damage components SparseArray
    /// @param lifes A ref to a LifeTime components SparseArray
    /// @param collisions A ref to a Collision components SparseArray
    DamageSystem(
        SparseArray<Component::Damage> &damages,
        SparseArray<Component::Life> &lifes,
        SparseArray<Component::Collision> &collisions,
        engine::Registry &registry
    );

    void operator()() override;

private:
    /// @brief this functions determines wether the collision
    /// deals damage or not
    /// @return returns true if the collision deals damage
    bool isDamageCollision(engine::Entity const collidedEntity);

    /// @brief This function damage the collided entity life component
    /// with the colliding entity damages component
    /// @param collidedEntity the entity wich receives the damages
    void damageEntity(engine::Entity const collidedEntity);

    /// @brief creates an explosion entity that represents the impact
    /// of the laser
    /// @param pos The position of the explosion
    void createExplosion(Component::Position pos);

    /// @brief creates an explosion entity that represents another entity
    /// exploding
    /// @param pos The position of the explosion
    void createBigExplosion(Component::Position pos);

    /// @brief A ref to a Damage components SparseArray
    SparseArray<Component::Damage> &_damages;
    /// @brief A ref to a LifeTime components SparseArray
    SparseArray<Component::Life> &_lifes;
    /// @brief A ref to a Collision components SparseArray
    SparseArray<Component::Collision> &_collisions;
    /// @brief A ref to the registry
    engine::Registry &_registry;
};

}
#endif /* !DAMAGESYSTEM_HPP_ */
