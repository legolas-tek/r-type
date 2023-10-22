/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Health Component
*/

#ifndef HEALTH_HPP_
#define HEALTH_HPP_

#include <cstddef>

#include "Serialization/Serializable.hpp"

namespace Component {

/**
 * @brief Structure representing an entity's Health.
 *
 * This structure is used to represent an entity's Health and stores its unique
 * identifier and Health value. It can be used as a component in a system for
 * managing the Health of entities.
 */
struct Health : engine::Serializable<Health> {
    /**
     * @brief Constructor for the Health structure.
     *
     * Initializes an instance of the Health structure with the specified
     * identifier and Health value.
     *
     * @param Health The Health value of the entity.
     * @param maxHealth The maximum of health the entity can have
     */
    explicit Health(int health, int maxHealth)
        : health(health)
        , maxHealth(maxHealth)
    {
    }

    /**
     * @brief Default constructor for the Health structure.
     */
    Health() = default;

    /**
     * @brief The Health value the entity curently has.
     */
    int health = 1;
    /// @brief The maximum amount of health the entity can have.
    int maxHealth = 1;
};
}

#endif /* !HEALTH_HPP_ */
