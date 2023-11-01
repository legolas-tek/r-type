/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Close event
*/

#ifndef R_TYPE_CLOSE_EVENT_HPP
#define R_TYPE_CLOSE_EVENT_HPP

#include "IEvent.hpp"

namespace Event {

class Close : public IEvent {
public:
    Close() = default;
    [[nodiscard]] EventType getType() const override
    {
        return EventType::CLOSE;
    }
};
}

#endif // R_TYPE_CLOSE_EVENT_HPP
