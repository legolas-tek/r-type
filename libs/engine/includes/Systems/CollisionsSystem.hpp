/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Collisions System
*/

#ifndef R_TYPE_COLLISIONSSYSTEM_HPP
#define R_TYPE_COLLISIONSSYSTEM_HPP

#include "ISystem.hpp"
#include "Registry.hpp"

#include "Components/Position.hpp"
#include "Components/HitBox.hpp"
#include "Components/HurtBox.hpp"

struct CollisionsSystem : public ISystem {
    CollisionsSystem(
        SparseArray<Component::Position> &positions,
        SparseArray<Component::HitBox> &hitboxes,
        SparseArray<Component::HurtBox> &hurtboxes
    );

    void operator()() override;

    SparseArray<Component::Position> &_positions;
    SparseArray<Component::HitBox> &_hitboxes;
    SparseArray<Component::HurtBox> &_hurtboxes;
};

#endif // R_TYPE_COLLISIONSSYSTEM_HPP
