/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Close event
*/

#ifndef R_TYPE_CLOSE_EVENT_HPP
#define R_TYPE_CLOSE_EVENT_HPP

#include "IEvent.hpp"

namespace event {

class Close : public IEvent {
    void dump(std::ostream &) const override;
};
}

#endif // R_TYPE_CLOSE_EVENT_HPP
