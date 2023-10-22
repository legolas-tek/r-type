/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Drawable Component
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include "Serialization/Serializable.hpp"

namespace Component {

/**
 * @brief Structure representing a drawable entity.
 *
 * This structure is used to represent a drawable entity and stores the index
 * to its associated resource in Registry::_assets_paths. It can be used as a
 * component in a system for managing drawable entities.
 */
struct Drawable : engine::Serializable<Drawable> {
public:
    /**
     * @brief Constructor for the Drawable structure.
     *
     * Initializes an instance of the Drawable structure with the specified
     * resource path.
     *
     * @param index The index to the resource, in the assets paths vector of the
     * registry.
     * @param width The width of the drawable entity in pixels.
     * @param height The height of the drawable entity in pixels.
     * @param scale The scale factor to apply to the drawable entity (default
     * is 1.0).
     * @param yOrigin The y origin of the drawable entity (default is 0.0).
     */
    Drawable(
        size_t index, float width, float height, float scale = 1.0f,
        float yOrigin = 0.0f
    )
        : _index(index)
        , _width(width)
        , _height(height)
        , _scale(scale)
        , _yOrigin(yOrigin)
    {
    }

    /**
     * @brief Default constructor for the Drawable structure.
     */
    Drawable() = default;

    size_t _index = 0; ///< The index to the associated resource in
                       ///< Registry::_assets_paths.
    float _width = 0.0f; ///< The width of the drawable entity in pixels.
    float _height = 0.0f; ///< The height of the drawable entity in pixels.
    float _scale = 1.0f; ///< The scale factor applied to the drawable entity.
    float _yOrigin = 0.0f; ///< The y origin of the drawable entity.
};

} // namespace Component

#endif /* !Drawable_HPP_ */
