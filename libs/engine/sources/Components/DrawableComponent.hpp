/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <cstddef>
#include <string>
#include <utility>

namespace Component {

/**
 * @brief Structure representing a drawable entity.
 *
 * This structure is used to represent a drawable entity and stores the path to
 * its associated resource. It can be used as a component in a system for
 * managing drawable entities.
 */
struct Drawable {
    /**
     * @brief Constructor for the Drawable structure.
     *
     * Initializes an instance of the Drawable structure with the specified
     * resource path.
     *
     * @param path The path to the resource associated with the drawable entity.
     */
    Drawable(std::string path)
        : _path(std::move(path))
    {
    }

    /**
     * @brief The path to the resource associated with the drawable entity.
     */
    std::string _path;
};

}

#endif /* !Drawable_HPP_ */
