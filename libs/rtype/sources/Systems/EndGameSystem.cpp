/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game Over Handler
*/

#include "EndGameSystem.hpp"
#include "Components/Focusable.hpp"
#include "Components/HitBox.hpp"
#include "Components/Position.hpp"
#include "Components/RestartOnClick.hpp"
#include "Components/Text.hpp"
#include "GameLoop.hpp"

static constexpr char const *FONT = "./assets/fonts/Over_There.ttf";

System::EndGameSystem::EndGameSystem(
    event::EventQueue &events, engine::Registry &registry
)
    : _events(events)
    , _registry(registry)
{
}

void System::EndGameSystem::operator()()
{
    if (_isEnded) {
        _cooldownToRestartServer--;
        if (_cooldownToRestartServer <= 0)
            throw GameEndException();
        return;
    }
    for (auto &end : _events.getEvents<event::EndGame>()) {
        _registry.reset_scene();
        using namespace Component;
        engine::Entity message(_registry.get_new_entity());
        engine::Entity button(_registry.get_new_entity());

        _registry.get_components<Position>().emplace_at(
            message, float(500), float(200)
        );
        _registry.get_components<Text>().emplace_at(
            message, end.win ? "You win" : "You lose", FONT, float(100),
            float(50)
        );

        _registry.get_components<Position>().emplace_at(button, 500, 500);
        _registry.get_components<Text>().emplace_at(
            button, "Restart", FONT, float(40), float(1)
        );
        _registry.get_components<Focusable>().emplace_at(button);
        _registry.get_components<HitBox>().emplace_at(button, 200, 100);
        _registry.get_components<RestartOnClick>().emplace_at(button);
        _isEnded = true;
    }
}