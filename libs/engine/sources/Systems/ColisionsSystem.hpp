/*
** EPITECH PROJECT, 2023
** engine
** File description:
** ColisionsSystem
*/

#ifndef COLISIONSSYSTEM_HPP_
#define COLISIONSSYSTEM_HPP_

#include "SparseArray.hpp"
#include "ISystem.hpp"

// #include "Components/HurtBoxComponent.hpp"    These commentarys are temporary
// #include "Components/HitBoxComponent.hpp"    they are here to compile

/// @brief This system launches an event depending if an entity hitboxe hit
/// and entity hurtbox
namespace System {

class ColisionsSystem : public ISystem {
    public:
        ColisionsSystem();
        ~ColisionsSystem();
    private:
};
}

#endif /* !COLISIONSSYSTEM_HPP_ */
