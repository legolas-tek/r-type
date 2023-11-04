/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Damage Handler System
*/

#ifndef R_TYPE_DAMAGE_HANDLER_SYSTEM_H
#define R_TYPE_DAMAGE_HANDLER_SYSTEM_H

#include "Components/Health.hpp"
#include "Events/EventQueue.hpp"
#include "ISystem.hpp"
#include "SparseArray.hpp"

namespace System {

class DamageHandler : public ISystem {
public:
    DamageHandler(
        SparseArray<Component::Health> &healths, event::EventQueue &events
    );

    void operator()() override;

private:
    SparseArray<Component::Health> &_healths;
    event::EventQueue &_events;
};

}

#endif // R_TYPE_DAMAGE_HANDLER_SYSTEM_H
