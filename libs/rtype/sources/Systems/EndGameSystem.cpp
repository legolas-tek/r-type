/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game Over Handler
*/

#include "EndGameSystem.hpp"
#include "Components/Position.hpp"
#include "Components/Text.hpp"

System::EndGameSystem::EndGameSystem(
    event::EventQueue &events, engine::Registry &registry
)
    : _events(events)
    , _registry(registry)
{
}

void System::EndGameSystem::operator()()
{
    for (auto &end : _events.getEvents<event::EndGame>()) {
        _registry.reset_scene();
        engine::Entity message(_registry.get_new_entity());
        _registry.get_components<Component::Position>().emplace_at(
            message, float(500), float(200)
        );
        _registry.get_components<Component::Text>().emplace_at(
            message, end.win ? "You win" : "You lose",
            "./assets/fonts/Over_There.ttf", float(100), float(50)
        );
    }
}