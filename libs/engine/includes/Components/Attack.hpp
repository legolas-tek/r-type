/*
** EPITECH PROJECT, 2023
** engine
** File description:
** Attack
*/

#ifndef ATTACK_HPP_
#define ATTACK_HPP_

#include "Serializable.hpp"

namespace Component {

/// @brief This struct is the component that represents the ability to attack
/// of an entity
struct Attack : Serializable<Attack> {
    Attack() = default;
    /// @brief A boolean that switch to true if and event triggers the attack
    bool is_attacking = false;
};
}

#endif /* !ATTACK_HPP_ */
