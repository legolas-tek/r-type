/*
** EPITECH PROJECT, 2023
** engine
** File description:
** ColisionsSystem
*/

#ifndef COLLISIONSSYSTEM_HPP_
#define COLLISIONSSYSTEM_HPP_

#include "ISystem.hpp"
#include "SparseArray.hpp"

#include "Components/Collision.hpp"
#include "Components/HitBox.hpp"

/// @brief This system launches an event depending if an entity hitbox hit
/// an other entity Hitbox
namespace System {

class ColisionsSystem : public ISystem {
    public:
        ColisionsSystem(
            SparseArray<Component::HitBox> const &hitBoxes,
            SparseArray<Component::Collision> &collisions
            ) : _hitBoxes(hitBoxes), _collisions(collisions) {}

        ColisionsSystem(System::ColisionsSystem const &other) = delete;

        ~ColisionsSystem() = default;
        void operator()() {
            // func logic
        }
    private:
        SparseArray<Component::HitBox> const &_hitBoxes;
        SparseArray<Component::Collision> &_collisions;
};
}

#endif /* !COLISIONSSYSTEM_HPP_ */
