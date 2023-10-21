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
#include "SparseArray.hpp"

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
     * \param controllables The registry of Controllable components.
     * \param velocities The registry of Velocity components.
     * \param playerNumber The player number to move.
     */
    Key(SparseArray<Component::Controllable> &controllables,
        SparseArray<Component::Velocity> &velocities,
        std::uint8_t playerNumber);

    /*!
     * \brief Destroy the Key system.
     *
     * Handles any necessary cleanup for the Key system upon its deletion.
     */
    ~Key() override;

    /*!
     * \brief Operator function to update entity velocities.
     *
     * Loops through all entities, and if they have both Velocity and
     * Controllable components, checks for user keyboard input (W/A/S/D) and
     * adjusts the entities' velocities accordingly.
     */
    void operator()() override;

private:
    SparseArray<Component::Controllable> &_controllables;
    SparseArray<Component::Velocity> &_velocities;
    std::uint8_t _playerNumber;
};
}
#endif /* !KEY_HPP_ */
