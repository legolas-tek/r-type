/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Rendering
*/

#ifndef RENDERING_HPP
#define RENDERING_HPP

#include <iostream>
#include <unordered_map>

#include "Components/Position.hpp"
#include "Entity.hpp"
#include "ISystem.hpp"
#include "Registry.hpp"
#include "RenderEntity.hpp"

#include "Components/Drawable.hpp"

namespace rendering::system {
/*!
 * \brief Constant integer value representing the screen width.
 */
int const SCREEN_WIDTH = 800;

/*!
 * \brief Constant integer value representing the screen height.
 */
int const SCREEN_HEIGHT = 450;

/*!
 * \class Rendering
 * \brief The Rendering class is responsible for rendering entities with
 * Drawable and Position components.
 *
 * This class manages the drawing of entities to the screen by iterating through
 * all entities, checking for Position and Drawable components, and drawing them
 * to the screen using raylib.
 */
class Rendering : public ISystem {
public:
    /*!
     * \brief Construct a new Rendering object.
     *
     * Initializes the Rendering system by storing a reference to the engine's
     * registry.
     *
     * \param registry Reference to the engine's registry to access entity
     * components.
     */
    explicit Rendering(engine::Registry &registry);

    /*!
     * \brief Destroy the Rendering object.
     *
     * Handles any necessary cleanup for the Rendering system upon its deletion.
     */
    ~Rendering() override;

    /*!
     * \brief Operator function to perform rendering of entities.
     *
     * Loops through all entities and if they have a Drawable and Position
     * component, renders them to the screen using raylib's drawing functions.
     * Textures may be cached for efficiency.
     */
    void operator()() override;

private:
    std::unordered_map<size_t, rendering::Entity>
        _cache; /*!< A cache mapping entity identifiers to Entity objects, for
                   efficient rendering.*/
    engine::Registry &_registry; /*!< Reference to the entity-component system's
                                    registry to manipulate entity data. */
};
} // namespace rendering

#endif // RENDERING_HPP
