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

#include "Components/Life.hpp"

namespace System {

/// @brief This system allows entities with the component life set to 0 to
/// die !!!!! This system should always be registered after the damage system if
/// you use both of them !!!!!!
class DeathSystem : public ISystem {

public:
    /// @brief constructs an instance of a DeathSystem class
    /// @param lifes A ref to a LifeTime components SparseArray
    /// @param reg A ref to the registry
    DeathSystem(SparseArray<Component::Life> &lifes, engine::Registry &reg);

    /// @brief applys the logic of the system
    void operator()() override;

private:
    SparseArray<Component::Life> &_lifes;
    engine::Registry &_reg;
    /// @brief A vector of entity to erase
    std::vector<engine::Entity> _toEraseEntityList;
};

}
#endif /* !DEATHSYSTEM_HPP_ */
