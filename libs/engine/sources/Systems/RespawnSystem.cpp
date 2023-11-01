/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** RespawnSystem
*/

#include "Systems/RespawnSystem.hpp"

System::RespawnSystem::RespawnSystem(
    SparseArray<Component::Life> &lifes,
    SparseArray<Component::Health> &healths,
    SparseArray<Component::Controllable> &controllables,
    SparseArray<Component::Drawable> &drawables,
    SparseArray<Component::Velocity> &velocities,
    SparseArray<Component::Collision> &collisions,
    SparseArray<Component::HitBox> &hitboxes, engine::Registry &reg,
    int respawnCooldown
)
    : _lifes(lifes)
    , _healths(healths)
    , _controllables(controllables)
    , _drawables(drawables)
    , _velocities(velocities)
    , _collisions(collisions)
    , _hitboxes(hitboxes)
    , _reg(reg)
    , _respawnCooldown(respawnCooldown)

{
}

void System::RespawnSystem::operator()()
{
    for (auto it = _lifes.begin(); it != _lifes.end(); it++) {
        if ((*it)->lifes > 0 && _healths[it.get_entity()]
            && _healths[it.get_entity()]->health == 0) {
            registerRespawnEntity(it.get_entity());
        }
    }
    for (auto &respawnTick : _respawnsTicks) {
        if (_reg.getTick() == respawnTick.second) {
            respawnEntity(respawnTick.first);
        }
    }
}

void System::RespawnSystem::registerRespawnEntity(engine::Entity entity)
{
    auto controllable = _controllables[entity];
    auto drawable = _drawables[entity];
    auto velocity = _velocities[entity];
    auto collision = _collisions[entity];
    auto hitbox = _hitboxes[entity];

    _respawnsTicks[entity] = _reg.getTick() + _respawnCooldown;
    if (drawable) {
        _drawableComps.emplace(entity, drawable.value());
        _reg.erase_component<Component::Drawable>(entity);
    }
    if (velocity) {
        _reg.erase_component<Component::Velocity>(entity);
    }
    if (controllable) {
        _controllableComps.emplace(entity, controllable.value());
        _reg.erase_component<Component::Controllable>(entity);
    }
    if (collision) {
        _collisionComps.emplace(entity, collision.value());
        _reg.erase_component<Component::Collision>(entity);
    }
    if (hitbox) {
        _hitboxComps.emplace(entity, hitbox.value());
        _reg.erase_component<Component::HitBox>(entity);
    }
    _healths[entity]->health = -1;
}

void System::RespawnSystem::respawnEntity(size_t entity)
{
    _lifes[entity]->lifes -= 1;
    _healths[entity]->health = _healths[entity]->maxHealth;
    _velocities[entity] = Component::Velocity(0, 0);
    if (_drawableComps.find(entity) != _drawableComps.end()) {
        _drawables[entity] = _drawableComps[entity];
        _drawableComps.erase(entity);
    }
    if (_controllableComps.find(entity) != _controllableComps.end()) {
        _controllables[entity] = _controllableComps[entity];
        _controllableComps.erase(entity);
    }
    if (_collisionComps.find(entity) != _collisionComps.end()) {
        _collisions[entity] = _collisionComps[entity];
        _collisionComps.erase(entity);
    }
    if (_hitboxComps.find(entity) != _hitboxComps.end()) {
        _hitboxes[entity] = _hitboxComps[entity];
        _hitboxComps.erase(entity);
    }
}
