/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ProcessKeyDownEvents
*/

#ifndef PROCESSKEYDOWNEVENTSSYSTEM_HPP_
#define PROCESSKEYDOWNEVENTSSYSTEM_HPP_

#include "ISystem.hpp"
#include "SparseArray.hpp"

#include "Components/Velocity.hpp"

#include "Events/EventQueue.hpp"

namespace System {

class ProcessKeyDownEvents : public ISystem {

public:
    ProcessKeyDownEvents(
        event::EventQueue &events, SparseArray<Component::Velocity> &velocities
    );

    void operator()() override;

private:
    event::EventQueue &_events;

    SparseArray<Component::Velocity> &_velocities;
};

}

#endif /* PROCESSKEYDOWNEVENTSSYSTEM_HPP_ */
