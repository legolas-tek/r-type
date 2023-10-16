/*
** EPITECH PROJECT, 2023
** engine
** File description:
** Attack
*/

#ifndef ATTACK_HPP_
#define ATTACK_HPP_

#include "Serializable.hpp"

/// @brief This struct is the component that represents the ability to attack
/// of an entity
namespace Component {

struct Attack : Serializable<Attack> {
    Attack() = default;
    /// @brief A boolean that switch to true if and event triggers the attack
    bool is_attacking = false;
    /// @brief the width of the entity
    float width;
};
}

#endif /* !ATTACK_HPP_ */
