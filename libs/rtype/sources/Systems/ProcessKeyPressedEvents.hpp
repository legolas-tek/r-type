/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ProcessKeyPressedEvents
*/

#ifndef R_TYPE_PROCESS_KEYPRESSED_EVENTS_SYSTEM_HPP_
#define R_TYPE_PROCESS_KEYPRESSED_EVENTS_SYSTEM_HPP_

#include "ISystem.hpp"
#include "SparseArray.hpp"

#include "Components/ChatModifiableText.hpp"
#include "Components/Text.hpp"

#include "Events/EventQueue.hpp"

namespace System {

inline constexpr int CHAT_COOLDOWN = 6;

class ProcessKeyPressedEvents : public ISystem {

public:
    ProcessKeyPressedEvents(
        event::EventQueue &events, std::size_t const &tick,
        SparseArray<Component::Text> &texts,
        SparseArray<Component::ChatModifiableText> &modifiables
    );

    void operator()() override;

private:
    event::EventQueue &_events;

    std::size_t const &_tick;
    std::size_t _previousTick;

    SparseArray<Component::Text> &_texts;
    SparseArray<Component::ChatModifiableText> &_modifiables;
};

}

#endif /* PROCESS_KEYPRESSED_EVENTS_SYSTEM_HPP_ */
