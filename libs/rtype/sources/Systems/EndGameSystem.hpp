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

namespace System {

class EndGameSystem : public ISystem {
public:
    EndGameSystem(event::EventQueue &events, engine::Registry &registry);
    ~EndGameSystem() override = default;
    void operator()() override;

private:
    event::EventQueue &_events;
    engine::Registry &_registry;
};

}

#endif // R_TYPE_GAMEOVER_SYSTEM_H
