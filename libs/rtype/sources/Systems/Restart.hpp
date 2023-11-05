/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Restart system
*/

#ifndef R_TYPE_RESTART_HPP
#define R_TYPE_RESTART_HPP

#include "Components/Focusable.hpp"
#include "Components/RestartOnClick.hpp"
#include "Events/EventQueue.hpp"
#include "ISystem.hpp"
#include "SparseArray.hpp"

namespace System {

class Restart : public ISystem {
public:
    Restart(
        event::EventQueue &events,
        SparseArray<Component::RestartOnClick> &controllables,
        SparseArray<Component::Focusable> &focusables
    );
    ~Restart() override = default;
    void operator()() override;

private:
    event::EventQueue &_events;
    SparseArray<Component::RestartOnClick> &_restarts;
    SparseArray<Component::Focusable> &_focusables;
};

}

#endif // R_TYPE_RESTART_HPP
