/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** RespawnSystem
*/

#include <iostream>

#include "Systems/RespawnSystem.hpp"

#include "Components/Controllable.hpp"
#include "Components/Velocity.hpp"
#include "Components/Position.hpp"

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
    _respawnsTicks[entity] = _reg.getTick() + _respawnCooldown;
    // TODO: Fix the rendering system so our ship can disapear properly
    if (_reg.get_components<Component::Drawable>()[entity]) {
        _drawableComps.emplace(
            entity,
            _reg.get_components<Component::Drawable>()[entity].value()
        );
        _reg.erase_component<Component::Drawable>(entity);
    }
    if (_reg.get_components<Component::Velocity>()[entity]) {
        _reg.get_components<Component::Velocity>()[entity]->_vx = 0;
        _reg.get_components<Component::Velocity>()[entity]->_vy = 0;
    }
    _reg.erase_component<Component::Controllable>(entity);
    _healths[entity]->health = -1;
}

void System::RespawnSystem::respawnEntity(size_t entity)
{
    _lifes[entity]->lifes -= 1;
    _healths[entity]->health = _healths[entity]->maxHealth;
    // TODO: Fix the rendering system so our ship can disapear properly
    _reg.get_components<Component::Drawable>().insert_at(
        entity,
        std::move(_drawableComps[entity])
    );
    std::cout << "respawn" << std::endl;
    // std::cout << "pos of top border = " << _reg.get_components<Component::Position>()[] << std::endl;
    _drawableComps.erase(entity);
    _reg.get_components<Component::Controllable>().insert_at(
        entity, Component::Controllable(1)
    );
}
