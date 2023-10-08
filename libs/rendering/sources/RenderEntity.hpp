/*! \class Entity
 *  \brief Brief class description
 *
 *  Detailed description
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "raylib.h"

#include <string>
#include <optional>

namespace rendering
{
class Entity {
public:
    Entity(std::string texture_path);
    Entity(const Entity&) = delete;
    Entity(Entity&&) = delete;

    ~Entity();

    Texture2D _texture;
private:
};
}


#endif //ENTITY_HPP
