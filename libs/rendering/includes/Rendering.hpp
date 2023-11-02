/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Rendering
*/

#ifndef RENDERING_HPP
#define RENDERING_HPP

#include "Entity.hpp"
#include "ISystem.hpp"
#include "Registry.hpp"

#include "Components/Animation.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"

namespace rendering::system {

/*!
 * \brief Constant integer value representing the screen width.
 */
inline constexpr int SCREEN_WIDTH = 1280;

/*!
 * \brief Constant integer value representing the screen height.
 */
inline constexpr int SCREEN_HEIGHT = 720;

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

    template <typename System, class... Params> void addSystem(Params &&...args)
    {
        _subSystems.emplace_back(
            std::make_unique<System>(std::forward<Params>(args)...)
        );
    }

private:
    /*!
     * \brief Reference to the registry to access entity components.
     */
    engine::Registry &_registry;

    /*!
     * \brief Vector of unique pointers to the sub systems.
     */
    std::vector<std::unique_ptr<ISystem>> _subSystems;
};

} // namespace rendering

#endif // RENDERING_HPP
