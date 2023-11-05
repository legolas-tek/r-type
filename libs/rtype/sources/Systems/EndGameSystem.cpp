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
#include "Rendering.hpp"

static constexpr char const *FONT = "./assets/fonts/Over_There.ttf";

System::EndGameSystem::EndGameSystem(
    event::EventQueue &events, engine::Registry &registry,
    ScoreManager &scoreManager
)
    : _events(events)
    , _registry(registry)
    , _scoreManager(scoreManager)
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
        engine::Entity score(_registry.get_new_entity());
        engine::Entity button(_registry.get_new_entity());

        _registry.get_components<Position>().emplace_at(
            message, rendering::system::SCREEN_WIDTH / 2, 200.f
        );
        _registry.get_components<Text>().emplace_at(
            message, end.win ? "You win" : "You lose", FONT, 75.f, 50.f
        );

        _registry.get_components<Position>().emplace_at(
            score, rendering::system::SCREEN_WIDTH / 2, 300.f
        );
        _registry.get_components<Text>().emplace_at(
            score, "Score " + std::to_string(_scoreManager.getScore()), FONT,
            25.f, 20.f
        );

        _registry.get_components<Position>().emplace_at(
            button, rendering::system::SCREEN_WIDTH / 2, 500.f
        );
        _registry.get_components<Text>().emplace_at(
            button, "Restart", FONT, 40.f, 1.f
        );
        _registry.get_components<Focusable>().emplace_at(button);
        _registry.get_components<HitBox>().emplace_at(button, 200, 100);
        _registry.get_components<RestartOnClick>().emplace_at(button);
        _isEnded = true;
    }
}
