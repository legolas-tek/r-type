/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Interface of events
*/

#ifndef R_TYPE_INTERFACE_EVENT_HPP
#define R_TYPE_INTERFACE_EVENT_HPP

namespace Event {

enum class EventType { COLLISION, CLOSE, MOUSE, UNDEFINED };

class IEvent {
public:
    virtual ~IEvent() = default;
    [[nodiscard]] virtual EventType getType() const = 0;
};

}

#endif // R_TYPE_INTERFACE_EVENT_HPP
