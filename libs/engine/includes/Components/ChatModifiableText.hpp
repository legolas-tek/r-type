/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Chat Modifiable Text Component
*/

#ifndef R_TYPE_CHAT_MODIFIABLE_TEXT_HPP
#define R_TYPE_CHAT_MODIFIABLE_TEXT_HPP

#include "Entity.hpp"

#include "Serialization/Serializable.hpp"

#include <cstddef>

namespace Component {

/**
 * @brief Structure representing a modifiable chat text.
 */
struct ChatModifiableText : engine::Serializable<ChatModifiableText> {

    ChatModifiableText(int id)
        : id(id)
    {
    }

    /// @brief default constructor
    ChatModifiableText() = default;

    /**
     * @brief The number of the player modifying the text
     */
    int id = 0;
};

}

#endif // R_TYPE_CHAT_MODIFIABLE_TEXT_HPP
