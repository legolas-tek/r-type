/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** TriggerBonus
*/

#ifndef R_TYPE_TRIGGER_BONUS_HPP_
#define R_TYPE_TRIGGER_BONUS_HPP_

#include "Registry.hpp"

#include "Components/Bonus.hpp"
#include "Components/Controllable.hpp"
#include "Components/Life.hpp"

namespace System {

/// @brief This system allows entities with the component Floating to move up
/// and down
class TriggerBonus : public ISystem {

public:
    /// @brief constructs an instance of a TriggerBonus class
    /// @param bonuses A ref to a Bonus components SparseArray
    /// @param controllables A ref to a Controllable components SparseArray
    /// @param lifes A ref to a Life components SparseArray
    /// @param reg A ref to the registry
    TriggerBonus(
        SparseArray<Component::Bonus> &bonuses,
        SparseArray<Component::Controllable> &controllables,
        SparseArray<Component::Life> &lifes, engine::Registry &reg
    );

    /// @brief applies the logic of the system
    void operator()() override;

private:
    /// @brief handles the process of granting the bonus to the player
    /// @param player the entity that represents the player that should
    /// receive the bonus
    /// @param bonus The entity that represents the bonus itself
    void processBonus(engine::Entity player, engine::Entity bonus);

    /// @brief Creates extra entities that shoot lasers around the player with a
    /// lifetime component
    /// @param player The entity that represents the player
    void createExtrasCannons(engine::Entity player);

    /// @brief A ref to a Bonus components SparseArray
    SparseArray<Component::Bonus> &_bonuses;
    /// @brief A ref to a Controllable components SparseArray
    SparseArray<Component::Controllable> &_controllables;
    /// @brief A ref to a Bonus components SparseArray
    SparseArray<Component::Life> &_lifes;
    /// @brief A ref to the registry
    engine::Registry &_reg;
};

}
#endif /* !R_TYPE_TRIGGER_BONUS_HPP_ */
