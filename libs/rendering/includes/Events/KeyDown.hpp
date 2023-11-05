/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** KeyDown Event
*/

#ifndef KEYDOWN_EVENT_H
#define KEYDOWN_EVENT_H

#include <string>

#include "Events/IEvent.hpp"

namespace event {

class KeyDown : public IEvent {

public:
    KeyDown(char key)
        : key(key)
    {
    }

    void dump(std::ostream &) const override;

    char key;
};

}

#endif /* KEYDOWN_EVENT_H */
