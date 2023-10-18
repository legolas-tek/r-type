/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DamageSystem
*/

#ifndef DAMAGESYSTEM_HPP_
#define DAMAGESYSTEM_HPP_

#include "ISystem.hpp"
#include "SparseArray.hpp"
#include "Registry.hpp"

#include "Components/Life.hpp"
#include "Components/Collision.hpp"
#include "Components/Damage.hpp"

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
    bool is_damage_collision(engine::Entity const collided_entity);

    /// @brief This function damage the collided entity life component
    /// with the colliding entity damages component
    /// @param collided_entity the entity wich receives the damages
    void damage_entity(engine::Entity const collided_entity);

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
