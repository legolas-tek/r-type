/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** KeyPressed Event
*/

#ifndef KEYPRESSED_EVENT_H
#define KEYPRESSED_EVENT_H

#include <string>

#include "Events/IEvent.hpp"

namespace event {

class KeyPressed : public IEvent {

public:
    KeyPressed(char key)
        : key(key)
    {
    }

    void dump(std::ostream &) const override;

    char key;
};

}

#endif /* KEYPRESSED_EVENT_H */
