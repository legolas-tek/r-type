/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Text Component
*/

#ifndef TEXT_COMPONENT_HPP_
#define TEXT_COMPONENT_HPP_

#include "Serializable.hpp"
#include <stddef.h>
#include <string>

namespace Component {

/**
 * @brief Structure representing text data.
 *
 * This structure is used to store text data for various purposes in a component-based system.
 */
struct Text : Serializable<Text> {
    /**
     * @brief Default constructor for the Text structure.
     */
    Text() = default;

    /**
     * @brief Constructor for the Text structure with a specified text.
     *
     * @param text The text to be stored in this structure.
     */
    explicit Text(std::string &&text, std::string &&font, float size, float spacing)
        : _text(std::move(text))
        , _font(std::move(font))
        , _size(size)
    {
    }

    /**
     * The text data stored in this structure.
     */
    std::string _text;

    /**
     * The font used to render the text.
     */
    std::string _font;

    /**
     * The size of the text.
     */
    float _size;

    /**
     * The spacing of the text.
     */
    float _spacing;
};

}

#endif
