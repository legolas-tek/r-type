/*
** EPITECH PROJECT, 2023
** engine
** File description:
** AttackSystem
*/

#include "Systems/AttackSystem.hpp"

#include "Components/Animation.hpp"
#include "Components/Collision.hpp"
#include "Components/Controllable.hpp"
#include "Components/Damage.hpp"
#include "Components/Drawable.hpp"
#include "Components/HitBox.hpp"
#include "Components/LifeTime.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

System::AttackSystem::AttackSystem(
    SparseArray<Component::FireRate> &fireRates,
    SparseArray<Component::Health> &healths,
    SparseArray<Component::Position> &positions, engine::Registry &reg
)
    : _fireRates(fireRates)
    , _healths(healths)
    , _positions(positions)
    , _register(reg)
{
}

void System::AttackSystem::operator()()
{
    for (auto it = _fireRates.begin(); it != _fireRates.end(); it++) {
        if (isAbleToAttack(it->value()) && _positions[it.get_entity()]) {
            createLaserEntity(engine::Entity(it.get_entity()));
        }
    }
}

void System::AttackSystem::createLaserEntity(engine::Entity const attacker_index
)
{
    if (_healths[attacker_index] && _healths[attacker_index]->health <= 0)
        return;
    Component::Velocity velocity(15, 0);
    engine::Entity attack_entity(_register.get_new_entity());
    Component::Position &attacker_pos = _positions[attacker_index].value();
    std::optional<Component::Collision> attacker_collision
        = _register.get_components<Component::Collision>()[attacker_index];
    Component::Position attack_entity_pos(attacker_pos);

    if (attacker_collision) {
        attack_entity_pos._x
            += (attacker_collision->_width / 2) + (LASER_WIDTH);
    }
    if (!_register.get_components<Component::Controllable>()[attacker_index]
        && attacker_collision) {
        velocity._vx = -15;
        attack_entity_pos._x = attacker_pos._x
            - (attacker_collision->_width / 2) - (LASER_WIDTH);
    }
    _positions.emplace_at(attack_entity, attack_entity_pos);
    _register.get_components<Component::Velocity>().insert_at(attack_entity, velocity
    );
    _register.get_components<Component::HitBox>().emplace_at(
        attack_entity, LASER_WIDTH, LASER_HEIGHT
    );
    _register.get_components<Component::Collision>().emplace_at(
        attack_entity, LASER_WIDTH, LASER_HEIGHT
    );
    _register.get_components<Component::Animation>().emplace_at(
        attack_entity, LASER_WIDTH * LASER_FRAMES, LASER_HEIGHT, LASER_WIDTH,
        LASER_HEIGHT, LASER_WIDTH, 10
    );
    _register.get_components<Component::Drawable>().emplace_at(
        attack_entity, LASER_INDEX, LASER_WIDTH, LASER_HEIGHT
    );
    _register.get_components<Component::LifeTime>().emplace_at(
        attack_entity, 200, _register.getTick()
    );
    _register.get_components<Component::Damage>().emplace_at(
        attack_entity, 1
    );
}

bool System::AttackSystem::isAbleToAttack(Component::FireRate &fire_rate)
{
    if (fire_rate.reload_ticks == 0)
        return true;
    return (_register.getTick() % fire_rate.reload_ticks == 0);
}
