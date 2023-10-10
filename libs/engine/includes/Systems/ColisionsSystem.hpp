/*
** EPITECH PROJECT, 2023
** engine
** File description:
** ColisionsSystem
*/

#ifndef COLISIONSSYSTEM_HPP_
#define COLISIONSSYSTEM_HPP_

#include "SparseArray.hpp"
#include "ISystem.hpp"

#include "Components/HitBox.hpp"
#include "Components/Collision.hpp"

/// @brief This system launches an event depending if an entity hitboxe hit
/// an other entity Hitbox
namespace System {

class ColisionsSystem : public ISystem {
    public:
        ColisionsSystem(
            SparseArray<Component::HitBox> const &hitBoxes,
            SparseArray<Component::Collision> const &collisions
            ) : _hitBoxes(hitBoxes), _collisions(collisions) {}
        ~ColisionsSystem();
        void operator()() {
            // func logic
        }
    private:
        SparseArray<Component::HitBox> const &_hitBoxes;
        SparseArray<Component::Collision> const &_collisions;
};
}

#endif /* !COLISIONSSYSTEM_HPP_ */
