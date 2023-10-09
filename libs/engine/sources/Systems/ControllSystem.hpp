/*
** EPITECH PROJECT, 2023
** engine
** File description:
** ControllSystem
*/

#ifndef CONTROLLSYSTEM_HPP_
#define CONTROLLSYSTEM_HPP_

#include "ISystem.hpp"
#include "SparseArray.hpp"

<<<<<<< HEAD
<<<<<<< HEAD
#include "Components/Controllable.hpp"
#include "Components/Velocity.hpp"

/// @brief This system allows the user to controll the entity by registering
/// the users inputs and changing components values
=======
#include "Components/ControllableComponent.hpp"
#include "Components/VelocityComponent.hpp"
=======
#include "Components/Controllable.hpp"
#include "Components/Velocity.hpp"
>>>>>>> 4f36685 (chore: uselesse includes and change includes in systems)

/// @brief This system allows the user to controll the entity by registering
//the users inputs and changing components values
>>>>>>> 6787844 (feat: add some doxygens on the systems)
namespace System {

class ControllSystem : public ISystem {
    public:
        ControllSystem(
            SparseArray<Component::Controllable> const &controllables,
            SparseArray<Component::Velocity> const &velocities
            )  : _controllables(controllables), _velocities(velocities) {}

            void operator()() {
                //system logic
            }

    private:
        SparseArray<Component::Controllable> const &_controllables;
        SparseArray<Component::Velocity> const &_velocities;
};
}

#endif /* !CONTROLLSYSTEM_HPP_ */
