/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Final boss event
*/

#ifndef R_TYPE_FINALBOSS_EVENT_HPP
#define R_TYPE_FINALBOSS_EVENT_HPP

#include "Entity.hpp"
#include "IEvent.hpp"

namespace event {

class FinalBoss : public IEvent {
public:
    FinalBoss(engine::Entity entity)
        : entity(entity)
    {
    }

    void dump(std::ostream &) const override;

    engine::Entity entity;
};

}

#endif // R_TYPE_FINALBOSS_EVENT_HPP
