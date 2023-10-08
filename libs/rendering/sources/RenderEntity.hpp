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
    Entity(std::string texture_path, std::optional<std::string> model_path);
    ~Entity();

    Texture2D _texture;
    Model _model;
private:
};
}


#endif //ENTITY_HPP
