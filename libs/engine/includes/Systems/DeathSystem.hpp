/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DeathSystem
*/

#ifndef DEATHSYSTEM_HPP_
#define DEATHSYSTEM_HPP_

#include "ISystem.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"

#include "Components/Health.hpp"
#include "Components/Life.hpp"
#include "Components/Dependent.hpp"
#include "Components/Follow.hpp"

namespace System {

/// @brief This system allows entities with the component life set to 0 to
/// die !!!!! This system should always be registered after the damage system if
/// you use both of them !!!!!!
class DeathSystem : public ISystem {

public:
    /// @brief constructs an instance of a DeathSystem class
    /// @param healths A ref to a Health components SparseArray
    /// @param reg A ref to the registry
    DeathSystem(
        SparseArray<Component::Health> &healths,
        SparseArray<Component::Life> &lifes,
        SparseArray<Component::Dependent> &dependents,
        SparseArray<Component::Follow> &follows, engine::Registry &reg
    );

    /// @brief applys the logic of the system
    void operator()() override;

private:
    /// @brief erase all the entity that depends on the entity given in param
    /// @param entity the entity on which others entity should depend to die
    void eraseDependentsEntities(engine::Entity entity);

    /// @brief checks whether an entity has already a death event raised or not
    /// @param entity the entity it checks
    /// @return returns true if the entity already ahs a death event and false
    /// if it doesn't
    bool isAlreadyInDeathEvent(engine::Entity entity) const;

    /// @brief A ref to a Health components SparseArray
    SparseArray<Component::Health> &_healths;
    /// @brief A ref to a Life components SparseArray
    SparseArray<Component::Life> &_lifes;
    /// @brief A ref to a Dependent components SparseArray
    SparseArray<Component::Dependent> &_dependents;
    /// @brief A ref to a Follow components SparseArray
    SparseArray<Component::Follow> &_follows;
    /// @brief A ref to the registry
    engine::Registry &_registry;
    /// @brief A vector of entity to erase
    std::vector<engine::Entity> _toEraseEntityList;
    /// @brief A ref to the EventQueue
    event::EventQueue &_events = _registry.events;
};

}
#endif /* !DEATHSYSTEM_HPP_ */
