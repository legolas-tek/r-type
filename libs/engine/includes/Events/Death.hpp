/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Death Event
*/

#ifndef R_TYPE_DEATH_EVENT_HPP
#define R_TYPE_DEATH_EVENT_HPP

#include "Entity.hpp"
#include "IEvent.hpp"

namespace event {

class Death : public IEvent {
public:
    Death(engine::Entity entity)
        : entity(entity)
    {
    }

    void dump(std::ostream &) const override;

    engine::Entity entity;
};
}

#endif // R_TYPE_DEATH_EVENT_HPP
