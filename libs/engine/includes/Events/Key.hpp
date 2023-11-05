/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Key
*/

#ifndef EVENT_KEY_HPP_
#define EVENT_KEY_HPP_

#include "IEvent.hpp"

namespace Event {

class Key : public event::IEvent {
public:
    Key(int key)
        : key(key)
    {
    }

    int key;
};
}
#endif /* !EVENT_KEY_HPP_ */
