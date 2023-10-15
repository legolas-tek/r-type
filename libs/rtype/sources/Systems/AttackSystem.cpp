/*
** EPITECH PROJECT, 2023
** engine
** File description:
** AttackSystem
*/

#include "Systems/AttackSystem.hpp"

#include "Components/HitBox.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Components/Drawable.hpp"
#include "Components/Controllable.hpp"

System::AttackSystem::AttackSystem(
    SparseArray<Component::Attack> &attacks,
    engine::Registry &reg
    ) : _attacks(attacks), _register(reg)
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
    Component::Attack &attack_comp,
    engine::Entity const attacker_index
    )
{
    Component::Velocity velocity(1, 0);
    SparseArray<Component::Position> &positions = _register.get_components<Component::Position>();
    engine::Entity attack_entity(_register.get_new_entity());
    Component::Position &attacker_pos = positions[attacker_index].value();
    Component::Position attack_entity_pos(
        attacker_pos._x + attack_comp.width + 1,
        attacker_pos._y + (attack_comp.height / 2)
        );

    if (_register.get_components<Component::Controllable>()[attacker_index]) {
        velocity._vx = -1;
        attack_entity_pos._x = attacker_pos._x - attack_comp.width - 1;
    }
    positions.emplace_at(attack_entity, std::move(attack_entity_pos));
    _register.get_components<Component::Velocity>().insert_at(attack_entity, std::move(velocity));
    _register.get_components<Component::HitBox>().insert_at(attack_entity, Component::HitBox());
    _register.get_components<Component::Drawable>().insert_at(attack_entity, Component::Drawable(LASER_INDEX));
    attack_comp.is_attacking = false;
}
