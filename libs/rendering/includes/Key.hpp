/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Key
*/

#ifndef KEY_HPP_
#define KEY_HPP_

#include "Components/Velocity.hpp"
#include "Components/Controllable.hpp"
#include "Registry.hpp"
#include "ISystem.hpp"
#include <raylib.h>


namespace rendering::system
{
/*!
 * \class Key
 * \brief The Key class is a system handling user input to affect entities' velocities.
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
         * \param registry Reference to the engine's registry to access entity components.
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
         * Loops through all entities, and if they have both Velocity and Controllable
         * components, checks for user keyboard input (W/A/S/D) and adjusts the
         * entities' velocities accordingly.
         */
        void operator()()
        {
            auto &velocity_list = _registry.get_components<Component::Velocity>();
            auto &controlable_list = _registry.get_components<Component::Controllable>();

            for (auto it = velocity_list.begin(); it != velocity_list.end(); ++it) {
                bool isControllable = controlable_list[it.get_entity()].has_value();
                velocity_list[it.get_entity()].value()._vx = 0.0f;
                velocity_list[it.get_entity()].value()._vy = 0.0f;

                if (isControllable) {
                    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_Z)) {
                        velocity_list[it.get_entity()].value()._vx += 0.0f;
                        velocity_list[it.get_entity()].value()._vy += -0.1f;
                    }
                    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_Q)) {
                        velocity_list[it.get_entity()].value()._vx += -0.1f;
                        velocity_list[it.get_entity()].value()._vy += 0.0f;
                    }
                    if (IsKeyDown(KEY_S)) {
                        velocity_list[it.get_entity()].value()._vx += 0.0f;
                        velocity_list[it.get_entity()].value()._vy += 0.1f;
                    }
                    if (IsKeyDown(KEY_D)) {
                        velocity_list[it.get_entity()].value()._vx += 0.1f;
                        velocity_list[it.get_entity()].value()._vy += 0.0f;
                    }
                }
            }
        }
    private:
        engine::Registry &_registry; /*!< Reference to the entity-component system's registry to manipulate entity data. */

};
}
#endif /* !KEY_HPP_ */
