/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Damage Event
*/

#ifndef R_TYPE_DAMAGE_EVENT_HPP
#define R_TYPE_DAMAGE_EVENT_HPP

#include "Entity.hpp"
#include "IEvent.hpp"

namespace event {

class Damage : public IEvent {
public:
    Damage(engine::Entity entity, int damages)
        : entity(entity)
        , damages(damages)
    {
    }

    void dump(std::ostream &) const override;

    engine::Entity entity;
    int damages;
};
}

#endif // R_TYPE_DAMAGE_EVENT_HPP
