/*
** EPITECH PROJECT, 2023
** engine
** File description:
** ColisionsSystem
*/

#ifndef COLLISIONSSYSTEM_HPP_
#define COLLISIONSSYSTEM_HPP_

#include "SparseArray.hpp"
#include "ISystem.hpp"

#include "Components/HitBox.hpp"
#include "Components/Collision.hpp"

/// @brief This system launches an event depending if an entity hitbox hit
/// an other entity Hitbox
namespace System {

class ColisionsSystem : public ISystem {
    public:
        ColisionsSystem(
            SparseArray<Component::HitBox> const &hitBoxes,
            SparseArray<Component::Collision> &collisions
            ) : _hitBoxes(hitBoxes), _collisions(collisions) {}
        ~ColisionsSystem();
        void operator()() {
            // func logic
        }
    private:
        SparseArray<Component::HitBox> const &_hitBoxes;
        SparseArray<Component::Collision> &_collisions;
};
}

#endif /* !COLISIONSSYSTEM_HPP_ */
