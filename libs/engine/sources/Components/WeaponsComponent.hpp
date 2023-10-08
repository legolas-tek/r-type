/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Weapons Component
*/

#ifndef WEAPONSCOMPONENT_HPP_
#define WEAPONSCOMPONENT_HPP_

#include "Serializable.hpp"

namespace Component {

/**
 * @brief Structure representing a weapons component.
 *
 * This structure is used to represent a weapons component associated with an
 * entity. It stores the unique identifier of the weapon. It can be used as a
 * component to manage the weapons of an entity.
 */
struct WeaponsComponent : Serializable<WeaponsComponent> {
    /**
     * @brief Constructor for the WeaponsComponent structure.
     *
     * Initializes an instance of the WeaponsComponent structure with the
     * specified weapon identifier.
     *
     * @param weaponId The unique identifier of the weapon associated with the
     * entity.
     */
    WeaponsComponent(int weaponId)
        : _weaponId(weaponId)
    {
    }

    /**
     * @brief The unique identifier of the weapon associated with the entity.
     */
    int _weaponId;
};

}

#endif /* !WEAPONSCOMPONENT_HPP_ */