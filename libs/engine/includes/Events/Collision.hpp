/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Collision event
*/

#ifndef R_TYPE_COLLISION_EVENT_H
#define R_TYPE_COLLISION_EVENT_H

#include "Entity.hpp"
#include "IEvent.hpp"

namespace Event {

class Collision : public IEvent {
public:
    Collision(engine::Entity entity, engine::Entity secondEntity)
        : entity(entity)
        , secondEntity(secondEntity) {};

    [[nodiscard]] EventType getType() const override
    {
        return EventType::COLLISION;
    };

    engine::Entity entity;
    engine::Entity secondEntity;
};

}

#endif // R_TYPE_COLLISION_EVENT_H
