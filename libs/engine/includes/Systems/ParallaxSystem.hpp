/*
** EPITECH PROJECT, 2023
** engine
** File description:
** ColisionsSystem
*/

#ifndef PARALLAXSYSTEM_HPP_
#define PARALLAXSYSTEM_HPP_

#include "ISystem.hpp"
#include "SparseArray.hpp"

#include "Registry.hpp"

/// @brief This system launches an event depending if an entity hitbox hit
/// an other entity Hitbox
namespace System {

class ParallaxSystem : public ISystem {
public:
    ParallaxSystem(engine::Registry &registry);
    void operator()() override;

private:
    engine::Registry &_registry;
};
}

#endif /* !PARALLAXSYSTEM_HPP_ */
