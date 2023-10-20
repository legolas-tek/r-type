/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Text Component
*/

#ifndef TEXT_COMPONENT_HPP_
#define TEXT_COMPONENT_HPP_

#include "Serialization/Deserializer.hpp"
#include "Serialization/Serializer.hpp"

#include <cstddef>
#include <cstdint>
#include <string>

namespace Component {

/**
 * @brief Structure representing text data.
 *
 * This structure is used to store text data for various purposes in a
 * component-based system.
 */
struct Text {
    /**
     * @brief Default constructor for the Text structure.
     */
    Text() = default;

    /**
     * @brief Constructor for the Text structure with a specified text.
     *
     * @param text The text to be stored in this structure.
     */
    explicit Text(
        std::string &&text, std::string &&font, float size, float spacing
    )
        : _text(std::move(text))
        , _font(std::move(font))
        , _size(size)
        , _spacing(spacing)
    {
    }

    void serialize(engine::Serializer &serializer) const
    {
        serializer.serializePascalString<std::uint32_t>(_text);
        serializer.serializePascalString<std::uint8_t>(_font);
        serializer.serializeTrivial(_size);
        serializer.serializeTrivial(_spacing);
    }

    void deserialize(engine::Deserializer &deserializer)
    {
        deserializer.deserializePascalString<std::uint32_t>(_text);
        deserializer.deserializePascalString<std::uint8_t>(_font);
        deserializer.deserializeTrivial(_size);
        deserializer.deserializeTrivial(_spacing);
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
