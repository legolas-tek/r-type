/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game Over Handler
*/

#ifndef R_TYPE_GAMEOVER_SYSTEM_H
#define R_TYPE_GAMEOVER_SYSTEM_H

#include "Events/End.hpp"
#include "Events/EventQueue.hpp"
#include "ISystem.hpp"
#include "Registry.hpp"
#include "ScoreManager.hpp"

namespace System {

class EndGameSystem : public ISystem {
public:
    EndGameSystem(
        event::EventQueue &events, engine::Registry &registry,
        ScoreManager &scoreManager
    );
    ~EndGameSystem() override = default;
    void operator()() override;

private:
    event::EventQueue &_events;
    engine::Registry &_registry;
    ScoreManager &_scoreManager;
    int _cooldownToRestartServer = 50;
    int _isEnded = false;
};

}

#endif // R_TYPE_GAMEOVER_SYSTEM_H
