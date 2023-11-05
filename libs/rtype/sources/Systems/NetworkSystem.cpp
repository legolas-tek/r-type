/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game-specific network system
*/

#include "Components/ChatModifiableText.hpp"
#include "Components/Controllable.hpp"
#include "Components/Text.hpp"
#include "Components/Velocity.hpp"

#include "NetworkServerSystem.hpp"
#include "NetworkSystem.hpp"

bool rtype::NetworkServerSystem::canUpdate(
    net::manager::Client const &client, engine::Entity entity,
    uint8_t component_id, [[maybe_unused]] engine::Deserializer deserializer
)
{
    auto &controllable
        = _registry.get_components<Component::Controllable>()[entity];
    auto &modifiable
        = _registry.get_components<Component::ChatModifiableText>()[entity];
    auto &texts = _registry.get_components<Component::Text>()[entity];

    if (not controllable or not modifiable or not texts)
        return false;
    if (_playerNumber != controllable->_id or _playerNumber != modifiable->id
        or not texts)
        return false;
    if (component_id == _registry.get_component_id<Component::Velocity>()
        or component_id == _registry.get_component_id<Component::Text>())
        return true;
}

bool rtype::NetworkClientSystem::canSend(
    engine::Entity entity, uint8_t component_id
)
{
    auto &controllable
        = _registry.get_components<Component::Controllable>()[entity];
    auto &modifiable
        = _registry.get_components<Component::ChatModifiableText>()[entity];
    auto &texts = _registry.get_components<Component::Text>()[entity];

    if (not controllable or not modifiable or not texts)
        return false;
    if (_playerNumber != controllable->_id or _playerNumber != modifiable->id
        or not texts)
        return false;
    if (component_id == _registry.get_component_id<Component::Velocity>()
        or component_id == _registry.get_component_id<Component::Text>())
        return true;
    // TODO: attack etc
    return false;
}
