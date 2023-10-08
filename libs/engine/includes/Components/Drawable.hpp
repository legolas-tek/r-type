/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Drawable Component
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include "Serializable.hpp"

namespace Component {

/**
 * @brief Structure representing a drawable entity.
 *
 * This structure is used to represent a drawable entity and stores the index
 * to its associated resource. It can be used as a component in a system for
 * managing drawable entities.
 */
struct Drawable : Serializable<Drawable> {
    /**
     * @brief Constructor for the Drawable structure.
     *
     * Initializes an instance of the Drawable structure with the specified
     * resource path.
     *
     * @param index The index to the resource associated with the drawable
     * entity.
     */
    Drawable(size_t index)
        : _index(index)
    {
    }

    /**
     * @brief The index to the resource associated with the drawable entity.
     */
    size_t _index;
};

}

#endif /* !Drawable_HPP_ */
