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

#include "Components/Controllable.hpp"
#include "Components/Velocity.hpp"

#include "Events/EventQueue.hpp"

namespace System {

class ProcessKeyDownEvents : public ISystem {

public:
    ProcessKeyDownEvents(
        event::EventQueue &events,
        SparseArray<Component::Controllable> &controllables,
        SparseArray<Component::Velocity> &velocities, std::size_t playerNumber
    );

    void operator()() override;

private:
    event::EventQueue &_events;

    SparseArray<Component::Controllable> &_controllables;
    SparseArray<Component::Velocity> &_velocities;

    std::size_t _playerNumber;
};

}

#endif /* PROCESSKEYDOWNEVENTSSYSTEM_HPP_ */
