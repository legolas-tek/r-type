/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** End Game Detection
*/

#ifndef R_TYPE_END_DETECT_H
#define R_TYPE_END_DETECT_H

#include "Components/Controllable.hpp"
#include "Events/End.hpp"
#include "Events/EventQueue.hpp"
#include "ISystem.hpp"
#include "SparseArray.hpp"

namespace System {

class End : public ISystem {
public:
    End(event::EventQueue &events,
        SparseArray<Component::Controllable> &controllables);
    ~End() override = default;
    void operator()() override;

private:
    bool hasControllables();
    bool isDefeat();
    bool finalBossDied();

    event::EventQueue &_events;
    SparseArray<Component::Controllable> &_controllables;

    int _defaultCooldown = 200;
    int _cooldown = _defaultCooldown;
    bool _finalBossSpawned = false;
    engine::Entity _finalBoss = engine::Entity(0);
};
}

#endif // R_TYPE_END_DETECT_H
