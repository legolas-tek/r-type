/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Text Component
*/

#ifndef TEXT_COMPONENT_HPP_
#define TEXT_COMPONENT_HPP_

#include "Serializable.hpp"
#include <iostream>
#include <stddef.h>
#include <string>

namespace Component {

/**
 * @brief Structure representing text data.
 *
 * This structure is used to store text data for various purposes in a component-based system.
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
    explicit Text(std::string &&text, std::string &&font, float size, float spacing)
        : _text(std::move(text))
        , _font(std::move(font))
        , _size(size)
    {
    }

    std::vector<std::byte> serialize() const
    {
        std::size_t offset = 0;
        std::vector<std::byte> vec(
            (sizeof(std::size_t) * 2)
            + (sizeof(char) * (_text.size() + _font.size())) + sizeof(_size)
            + sizeof(_spacing)
        );

        std::size_t stringSize = _text.size();

        std::memcpy(vec.data(), &stringSize, sizeof(stringSize));
        offset += sizeof(stringSize);
        std::memcpy(
            vec.data() + offset, _text.data(), sizeof(char) * stringSize
        );
        offset += sizeof(char) * stringSize;

        stringSize = _font.size();

        std::memcpy(vec.data() + offset, &stringSize, sizeof(stringSize));
        offset += sizeof(stringSize);
        std::memcpy(
            vec.data() + offset, _font.data(), sizeof(char) * stringSize
        );
        offset += sizeof(char) * stringSize;

        std::memcpy(vec.data() + offset, &_size, sizeof(_size));
        offset += sizeof(_size);
        std::memcpy(vec.data() + offset, &_spacing, sizeof(_spacing));
        offset += sizeof(_spacing);

        return vec;
    }

    size_t deserialize(std::byte const *buffer)
    {
        std::size_t offset = 0;

        std::size_t stringSize = 0;
        std::memcpy(&stringSize, buffer, sizeof(stringSize));
        offset += sizeof(stringSize);

        this->_text.resize(stringSize);
        this->_text.insert(
            0, reinterpret_cast<char const *>(buffer + offset), stringSize
        );
        offset += stringSize;

        std::memcpy(&stringSize, buffer, sizeof(stringSize));
        offset += sizeof(stringSize);

        this->_font.resize(stringSize);
        this->_font.insert(
            0, reinterpret_cast<char const *>(buffer + offset), stringSize
        );
        offset += stringSize;

        std::memcpy(&_size, buffer + offset, sizeof(_size));
        offset += sizeof(_size);
        std::memcpy(&_spacing, buffer + offset, sizeof(_size));
        offset += sizeof(_spacing);

        return offset;
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
