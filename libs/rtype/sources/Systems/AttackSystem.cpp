/*
** EPITECH PROJECT, 2023
** engine
** File description:
** AttackSystem
*/

#include <iostream>

#include "Systems/AttackSystem.hpp"

#include "Components/Collision.hpp"
#include "Components/HitBox.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Components/Drawable.hpp"
#include "Components/Controllable.hpp"

System::AttackSystem::AttackSystem(
    SparseArray<Component::Attack> &attacks, engine::Registry &reg
)
    : _attacks(attacks)
    , _register(reg)
{
}

void System::AttackSystem::operator()()
{
    for (auto it = _attacks.begin(); it != _attacks.end(); it++) {
        if (it->value().is_attacking) {
            createLaserEntity(it->value(), engine::Entity(it.get_entity()));
        }
    }
}

void System::AttackSystem::createLaserEntity(
    Component::Attack &attack_comp, engine::Entity const attacker_index
)
{
    size_t laser_index = 2;
    Component::Velocity velocity(15, 0);
    SparseArray<Component::Position> &positions
        = _register.get_components<Component::Position>();
    engine::Entity attack_entity(_register.get_new_entity());
    Component::Position &attacker_pos = positions[attacker_index].value();
    std::optional<Component::Collision> attacker_collision =
        _register.get_components<Component::Collision>()[attacker_index];
    Component::Position attack_entity_pos(attacker_pos);

    if (attacker_collision) {
        attack_entity_pos._x += (attacker_collision->_width / 2) + 1;
    }
    if (!_register.get_components<Component::Controllable>()[attacker_index] && attacker_collision) {
        velocity._vx = -15;
        attack_entity_pos._x = attacker_pos._x - (attacker_collision->_width / 2) - 1;
    }
    positions.emplace_at(attack_entity, std::move(attack_entity_pos));
    _register.get_components<Component::Velocity>().emplace_at(
        attack_entity, std::move(velocity)
    );
    _register.get_components<Component::HitBox>().insert_at(
        attack_entity, Component::HitBox(32, 2)
    );
    _register.get_components<Component::Drawable>().insert_at(
        attack_entity, Component::Drawable(laser_index, 32, 2)
    );
    attack_comp.is_attacking = false;
}
