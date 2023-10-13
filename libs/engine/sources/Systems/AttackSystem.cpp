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
            engine::Entity attack_entity(_register.get_new_entity());
            SparseArray<Component::Position> &positions = _register.get_components<Component::Position>();

            positions.emplace_at(attack_entity, positions[it.get_entity()]);
            _register.get_components<Component::Velocity>().insert_at(attack_entity, Component::Velocity(1, 0));
            _register.get_components<Component::HitBox>().insert_at(attack_entity, Component::HitBox());
            _register.get_components<Component::Drawable>().insert_at(attack_entity, Component::Drawable(attack_entity));
        }
}
}
