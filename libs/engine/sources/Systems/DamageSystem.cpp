/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DamageSystem
*/

#include "Systems/DamageSystem.hpp"

System::DamageSystem::DamageSystem(
    SparseArray<Component::Damage> &damages,
    SparseArray<Component::Life> &lifes,
    SparseArray<Component::Collision> &collisions, engine::Registry &registry
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

    return (_lifes[collidedEntity] && _damages[collidingEntity]);
}

void System::DamageSystem::damageEntity(engine::Entity const collidedEntity)
{
    engine::Entity const collidingEntity
        = _collisions[collidedEntity]->_collidingEntity.value();

    _lifes[collidedEntity]->life -= _damages[collidingEntity]->damages;
    _registry.erase_entity(collidingEntity);
    if (_lifes[collidedEntity]->life <= 0)
        _registry.erase_entity(collidedEntity);
}
