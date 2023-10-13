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

#include "Components/Collision.hpp"
#include "Components/HitBox.hpp"

/// @brief This system launches an event depending if an entity hitbox hit
/// an other entity Hitbox
namespace System {

class AnimationSystem : public ISystem {
public:
    AnimationSystem(engine::Registry &registry)
    : _registry(registry)
    {
    }
    // ~AnimationSystem();
    void operator()()
    {
        // DrawTextureRec(scarfy, frameRec, position, WHITE);  // Draw part of the texture

        std::cout << "Asd" << std::endl;
        // func logic
    }

private:
    engine::Registry &_registry;
};
}

#endif /* !ANIMATIONSYSTEM_HPP_ */
