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

#include "Components/Animation.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

/// @brief This system launches an event depending if an entity hitbox hit
/// an other entity Hitbox
namespace System {

class AnimationSystem : public ISystem {
public:
    AnimationSystem(engine::Registry &registry);
    // ~AnimationSystem();
    void operator()() override;

private:
    engine::Registry &_registry;
};
}

#endif /* !ANIMATIONSYSTEM_HPP_ */
