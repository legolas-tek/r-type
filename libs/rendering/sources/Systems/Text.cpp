/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Text
*/

#include "Systems/Text.hpp"

rendering::Text::Text(
    SparseArray<Component::Text> &texts,
    SparseArray<Component::Position> &positions
)
    : _texts(texts)
    , _positions(positions)
{
}

bool rendering::Text::FontIsLoaded(std::string const &path)
{
    return _cache.find(path) != _cache.end();
}

void rendering::Text::operator()()
{
    for (auto it = _texts.begin(); it != _texts.end(); ++it) {
        size_t index = it.get_entity();

        if (not _positions[index].has_value())
            continue;

        if (not FontIsLoaded((*it)->_font))
            _cache[(*it)->_font] = LoadFont((*it)->_font.c_str());

        auto &font = _cache[(*it)->_font];
        auto &pos = _positions[index];

        DrawTextEx(
            font, (*it)->_text.c_str(), Vector2 { pos->_x, pos->_y },
            (*it)->_size, 0, BLACK
        );
    }
}