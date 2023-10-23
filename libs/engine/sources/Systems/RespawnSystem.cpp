/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** RespawnSystem
*/

#include "Systems/RespawnSystem.hpp"

#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

System::RespawnSystem::RespawnSystem(
    SparseArray<Component::Life> &lifes,
    SparseArray<Component::Health> &healths, engine::Registry &reg,
    int respawnCooldown
)
    : _lifes(lifes)
    , _healths(healths)
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
    auto controllables = _reg.get_components<Component::Controllable>()[entity];
    auto drawables = _reg.get_components<Component::Drawable>()[entity];
    auto velocities = _reg.get_components<Component::Velocity>()[entity];

    _respawnsTicks[entity] = _reg.getTick() + _respawnCooldown;
    if (drawables) {
        _drawableComps.emplace(entity, drawables.value());
        _reg.erase_component<Component::Drawable>(entity);
    }
    if (velocities) {
        velocities->_vx = 0;
        velocities->_vy = 0;
    }
    if (controllables) {
        _controllableComps.emplace(entity, controllables.value());
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
