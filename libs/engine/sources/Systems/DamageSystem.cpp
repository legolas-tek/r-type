/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DamageSystem
*/

#include <iostream>

#include "Systems/DamageSystem.hpp"

System::DamageSystem::DamageSystem(
    SparseArray<Component::Damage> &damages,
    SparseArray<Component::Life> &lifes,
    SparseArray<Component::Collision> &collisions,
    engine::Registry &registry
)
    : _damages(damages)
    , _lifes(lifes)
    , _collisions(collisions)
    , _registry(registry)
{
}

void System::DamageSystem::operator()()
{
    for (auto it = _collisions.begin(); it != _collisions.end(); it++) {
        std::cout << "test = " << (*it)->_collidingEntity.has_value() << std::endl;
        if ((*it)->_collidingEntity && is_damage_collision(it.get_entity())) {
            damage_entity(it.get_entity());
            std::cout << "damage dealt to entity: " << it.get_entity() << std::endl;
        }
    }
}

bool System::DamageSystem::is_damage_collision(
    engine::Entity const collided_entity
)
{
    engine::Entity const colliding_entity =
        _collisions[collided_entity]->_collidingEntity.value();

    return (_lifes[collided_entity] && _damages[colliding_entity]);
}

void System::DamageSystem::damage_entity(engine::Entity const collided_entity)
{
    engine::Entity const colliding_entity =
        _collisions[collided_entity]->_collidingEntity.value();

    _lifes[collided_entity]->life -= _damages[colliding_entity]->damages;
    if (_lifes[collided_entity]->life <= 0)
        _registry.erase_entity(colliding_entity);
}
