/*
** EPITECH PROJECT, 2023
** engine
** File description:
** ColisionsSystem
*/

#ifndef ANIMATIONSYSTEM_HPP_
#define ANIMATIONSYSTEM_HPP_

#include "ISystem.hpp"
#include "SparseArray.hpp"

#include "Registry.hpp"

namespace System {

/// @brief This system launches an event depending if an entity hitbox hit
/// an other entity Hitbox
class AnimationSystem : public ISystem {
public:
    explicit AnimationSystem(engine::Registry &registry);
    // ~AnimationSystem();
    void operator()() override;

private:
    engine::Registry &_registry;
};
}

#endif /* !ANIMATIONSYSTEM_HPP_ */
