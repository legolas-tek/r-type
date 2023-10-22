/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Text
*/

#include "Systems/Text.hpp"

rendering::system::Text::Text(
    SparseArray<Component::Text> &texts,
    SparseArray<Component::Position> &positions
)
    : _texts(texts)
    , _positions(positions)
{
}

rendering::system::Text::~Text()
{
    for (auto &font : _cache)
        UnloadFont(font.second);
}

bool rendering::system::Text::isFontLoaded(std::string const &path)
{
    return _cache.find(path) != _cache.end();
}

void rendering::system::Text::operator()()
{
    for (auto it = _texts.begin(); it != _texts.end(); ++it) {
        size_t index = it.get_entity();
        auto &text = **it;

        if (not _positions[index].has_value())
            continue;

        if (not isFontLoaded(text._font))
            _cache[text._font] = LoadFont(text._font.c_str());

        auto &font = _cache[text._font];
        auto &pos = _positions[index];

        Vector2 measure = MeasureTextEx(
            font, text._text.c_str(), text._size, text._spacing
        );

        DrawTextEx(
            font, text._text.c_str(),
            Vector2 { pos->_x - measure.x / 2, pos->_y - measure.y / 2 },
            text._size, text._spacing, BLACK
        );
    }
}
