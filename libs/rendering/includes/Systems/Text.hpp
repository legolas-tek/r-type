/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Text
*/

#ifndef R_TYPE_TEXT_HPP
#define R_TYPE_TEXT_HPP

#include "Components/Position.hpp"
#include "Components/Text.hpp"
#include "ISystem.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"
#include "raylib.h"

namespace rendering::system {

/// @brief A system for rendering text components.
struct Text : public ISystem {
    /// @brief Constructor for the Text system.
    /// @param texts A reference to the texts component storage.
    /// @param positions A reference to the positions component storage.
    Text(
        SparseArray<Component::Text> &texts,
        SparseArray<Component::Position> &positions
    );

    /// @brief Destructor for the Text system.
    ~Text() override;

    /// @brief Operator to execute the Text system.
    void operator()() override;

private:
    /// @brief Check if a font is already loaded.
    /// @param path The path to the font file.
    /// @return True if the font is loaded, false otherwise.
    bool isFontLoaded(std::string const &path);

    SparseArray<Component::Text> &_texts;
    SparseArray<Component::Position> &_positions;
    std::unordered_map<std::string, Font> _cache;
};

} // namespace rendering::system

#endif // R_TYPE_TEXT_HPP
