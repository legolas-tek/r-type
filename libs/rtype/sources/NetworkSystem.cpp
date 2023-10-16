/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game-specific network system
*/

#include "NetworkSystem.hpp"
#include "Components/Controllable.hpp"
#include "Components/Velocity.hpp"
#include "NetworkServerSystem.hpp"

bool rtype::NetworkServerSystem::canUpdate(
    engine::Entity entity, uint8_t component_id,
    [[maybe_unused]] std::byte const *buffer
)
{
    auto &controllable
        = _registry.get_components<Component::Controllable>()[entity];
    if (!controllable)
        return false;
    // TODO: check player ID
    if (component_id == _registry.get_component_id<Component::Velocity>())
        return true;
    // TODO: attack etc
    return false;
}