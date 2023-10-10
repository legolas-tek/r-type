/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Key
*/

#ifndef KEY_HPP_
#define KEY_HPP_

#include "Components/Controllable.hpp"
#include "Components/Velocity.hpp"
#include "ISystem.hpp"
#include "Registry.hpp"
#include <raylib.h>

namespace rendering::system {
/*!
 * \class Key
 * \brief The Key class is a system handling user input to affect entities'
 * velocities.
 *
 * This class fetches all entities with a Velocity component and adjusts their
 * velocity based on user keyboard input if they have a Controllable component.
 */
class Key : public ISystem {
public:
    /*!
     * \brief Construct a Key system.
     *
     * Construct the Key system by initializing its entity registry.
     *
     * \param registry Reference to the engine's registry to access entity
     * components.
     */
    Key(engine::Registry &registry);

    /*!
     * \brief Destroy the Key system.
     *
     * Handles any necessary cleanup for the Key system upon its deletion.
     */
    ~Key();

    /*!
     * \brief Operator function to update entity velocities.
     *
     * Loops through all entities, and if they have both Velocity and
     * Controllable components, checks for user keyboard input (W/A/S/D) and
     * adjusts the entities' velocities accordingly.
     */
    void operator()() override;

private:
    engine::Registry &_registry; /*!< Reference to the entity-component system's
                                    registry to manipulate entity data. */
};
}
#endif /* !KEY_HPP_ */
