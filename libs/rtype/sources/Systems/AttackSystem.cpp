/*
** EPITECH PROJECT, 2023
** engine
** File description:
** AttackSystem
*/

#include "Systems/AttackSystem.hpp"

#include "Components/Collision.hpp"
#include "Components/Controllable.hpp"
#include "Components/Drawable.hpp"
#include "Components/HitBox.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

System::AttackSystem::AttackSystem(
    SparseArray<Component::FireRate> &fireRates, engine::Registry &reg
)
    : _fireRates(fireRates)
    , _register(reg)
{
}

void System::AttackSystem::operator()()
{
    for (auto it = _fireRates.begin(); it != _fireRates.end(); it++) {
        if (isAbleToAttack(it->value())) {
            createLaserEntity(engine::Entity(it.get_entity()));
        }
    }
}

void System::AttackSystem::createLaserEntity(
    engine::Entity const attacker_index
)
{
    size_t laser_index = 4;
    Component::Velocity velocity(15, 0);
    SparseArray<Component::Position> &positions
        = _register.get_components<Component::Position>();
    engine::Entity attack_entity(_register.get_new_entity());
    Component::Position &attacker_pos = positions[attacker_index].value();
    std::optional<Component::Collision> attacker_collision
        = _register.get_components<Component::Collision>()[attacker_index];
    Component::Position attack_entity_pos(attacker_pos);

    if (attacker_collision) {
        attack_entity_pos._x += (attacker_collision->_width / 2) + 1;
    }
    if (!_register.get_components<Component::Controllable>()[attacker_index]
        && attacker_collision) {
        velocity._vx = -15;
        attack_entity_pos._x
            = attacker_pos._x - (attacker_collision->_width / 2) - 1;
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
}

bool System::AttackSystem::isAbleToAttack(Component::FireRate &fire_rate)
{
    return (_register.getTick() % fire_rate.reload_ticks == 0);
}
