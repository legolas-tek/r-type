/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DamageSystem
*/

#include "Systems/DamageSystem.hpp"

System::DamageSystem::DamageSystem(
    SparseArray<Component::Damage> &damages,
    SparseArray<Component::Health> &healths,
    SparseArray<Component::Collision> &collisions, engine::Registry &registry
)
    : _damages(damages)
    , _healths(healths)
    , _collisions(collisions)
    , _registry(registry)
{
}

void System::DamageSystem::operator()()
{
    for (auto it = _collisions.begin(); it != _collisions.end(); it++) {
        if ((*it)->_collidingEntity && isDamageCollision(it.get_entity())) {
            damageEntity(it.get_entity());
        }
    }
}

bool System::DamageSystem::isDamageCollision(engine::Entity const collidedEntity
)
{
    engine::Entity const collidingEntity
        = _collisions[collidedEntity]->_collidingEntity.value();

    return (_healths[collidedEntity] && _damages[collidingEntity]);
}

void System::DamageSystem::damageEntity(engine::Entity const collidedEntity)
{
    engine::Entity const collidingEntity
        = _collisions[collidedEntity]->_collidingEntity.value();

    _healths[collidedEntity]->health -= _damages[collidingEntity]->damages;
}
