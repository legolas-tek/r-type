/*! \class Entity
 *  \brief Brief class description
 *
 *  Detailed description
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <raylib.h>

#include <optional>
#include <string>

namespace rendering {
class Entity {
public:
    Entity(std::string texture_path);
    Entity(Entity const &) = delete;
    Entity(Entity &&) = delete;
    Entity &operator=(Entity const &) = delete;
    Entity &operator=(Entity &&) = delete;

    ~Entity();

    Texture2D _texture;
};
}

#endif // ENTITY_HPP
