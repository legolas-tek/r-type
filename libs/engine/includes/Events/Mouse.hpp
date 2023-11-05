/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Mouse Event
*/

#ifndef R_TYPE_MOUSE_EVENT_HPP
#define R_TYPE_MOUSE_EVENT_HPP

#include "IEvent.hpp"

namespace event {

enum class MouseEventType { RIGHT, LEFT, MIDDLE };

class Mouse : public IEvent {
public:
    Mouse(float x, float y, MouseEventType type)
        : x(x)
        , y(y)
        , type(type)
    {
    }

    void dump(std::ostream &) const override;

    float x;
    float y;
    MouseEventType type;
};

}

#endif // R_TYPE_MOUSE_EVENT_HPP
