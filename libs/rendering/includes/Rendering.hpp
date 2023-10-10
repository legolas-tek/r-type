/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Rendering
*/

#ifndef RENDERING_HPP
    #define RENDERING_HPP

#include <unordered_map>
#include <iostream>

#include <raylib.h>
#include "Entity.hpp"
#include "RenderEntity.hpp"
#include "Registry.hpp"
#include "ISystem.hpp"
#include "Components/Position.hpp"

#include "Components/Drawable.hpp"

namespace rendering::system
{
/*!
 * \brief Constant integer value representing the screen width.
 */
const int SCREEN_WIDTH  = 800;

/*!
 * \brief Constant integer value representing the screen height.
 */
const int SCREEN_HEIGHT = 450;

/*!
 * \class Rendering
 * \brief The Rendering class is responsible for rendering entities with Drawable and Position components.
 *
 * This class manages the drawing of entities to the screen by iterating through all entities,
 * checking for Position and Drawable components, and drawing them to the screen using raylib.
 */
class Rendering : public ISystem {
public:
    /*!
     * \brief Construct a new Rendering object.
     *
     * Initializes the Rendering system by storing a reference to the engine's registry.
     *
     * \param registry Reference to the engine's registry to access entity components.
     */
    Rendering(engine::Registry &registry);

    /*!
     * \brief Destroy the Rendering object.
     *
     * Handles any necessary cleanup for the Rendering system upon its deletion.
     */
    ~Rendering();

    /*!
     * \brief Operator function to perform rendering of entities.
     *
     * Loops through all entities and if they have a Drawable and Position component,
     * renders them to the screen using raylib's drawing functions. Textures may be cached
     * for efficiency.
     */
    void operator()()
    {
        std::size_t index = 0;
        auto drawable_list = _registry.get_components<Component::Drawable>();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (auto it = drawable_list.begin(); it != drawable_list.end(); ++it) {
            auto pos = _registry.get_components<Component::Position>()[it.get_entity()];

            if (_cache.find(it.get_entity()) != _cache.end()) {
                DrawTexture(_cache.at(it.get_entity())._texture, pos->_x, pos->_y, WHITE);
            } else {
                _cache.emplace(it.get_entity(), _registry._assets_paths[(*it)->_index]);
                DrawTexture(_cache.at(it.get_entity())._texture, pos->_x, pos->_y, WHITE);
            }
        }
        EndDrawing();
    }

private:
    std::unordered_map<size_t, rendering::Entity> _cache;
    engine::Registry &_registry;
};
} // namespace rendering


#endif //RENDERING_HPP
