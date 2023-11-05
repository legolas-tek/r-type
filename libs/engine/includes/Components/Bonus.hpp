/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Bonus
*/

#ifndef R_TYPE_BONUS_HPP_
#define R_TYPE_BONUS_HPP_

#include "Serialization/Serializable.hpp"

namespace Component {

/// @brief This component allows our entity to grant a bonus to a controllable
/// entity that collides with itself
struct Bonus : engine::Serializable<Bonus> {
    /// @brief An enum that defines all the types of bonus an entity can have
    enum BonusTypes { LIFE, WEAPON, NONE };

    /// @brief Constructs an instance of a Bonus component and sets the
    /// type of bonus it grants
    /// @param Bonus The type of bonus it grants
    Bonus(BonusTypes bonusType)
        : bonusType(bonusType)
    {
    }

    /// @brief Default constructor
    Bonus() = default;

    BonusTypes bonusType = NONE;
};

}
#endif /* !R_TYPE_BONUS_HPP_ */
