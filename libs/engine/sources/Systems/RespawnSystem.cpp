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
        engine::Registry &reg, int respawnCooldown
)
    : _lifes(lifes)
    , _healths(healths)
    , _controllables(controllables)
    , _drawables(drawables)
    , _velocities(velocities)
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

    _respawnsTicks[entity] = _reg.getTick() + _respawnCooldown;
    if (drawable) {
        _drawableComps.emplace(entity, drawable.value());
        _reg.erase_component<Component::Drawable>(entity);
    }
    if (velocity) {
        velocity->_vx = 0;
        velocity->_vy = 0;
    }
    if (controllable) {
        _controllableComps.emplace(entity, controllable.value());
        _reg.erase_component<Component::Controllable>(entity);
    }
    _healths[entity]->health = -1;
}

void System::RespawnSystem::respawnEntity(size_t entity)
{
    _lifes[entity]->lifes -= 1;
    _healths[entity]->health = _healths[entity]->maxHealth;
    _reg.get_components<Component::Drawable>()[entity] = _drawableComps[entity];
    _drawableComps.erase(entity);
    _reg.get_components<Component::Controllable>()[entity] =
        _controllableComps[entity];
    _controllableComps.erase(entity);
}
