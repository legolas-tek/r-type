/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** LootDropManager
*/

#ifndef R_TYPE_LOOTDROPMANAGER_HPP_
#define R_TYPE_LOOTDROPMANAGER_HPP_

#include <random>

#include "Registry.hpp"

#include "Components/Loot.hpp"
#include "Components/Position.hpp"

namespace System {

/// @brief This system allows entities with the component Loot to have a
/// percentage of chances to drop a random bonus at death
class LootDropManager : public ISystem {

public:
    /// @brief constructs an instance of a LootDropManager class
    /// @param loots A ref to a Loot components SparseArray
    /// @param positions A ref to a Position components SparseArray
    /// @param chancesToDrop The percentage of chances entities will have to
    /// drop a bonus
    LootDropManager(
        SparseArray<Component::Loot> &loots,
        SparseArray<Component::Position> &positions, engine::Registry &reg,
        float chancesToDrop
    );

    /// @brief applies the logic of the system
    void operator()() override;

private:
    /// @brief This method checks wether the entity has a position and is able
    /// to createBonus using a rand function and the _chancesToDrop variable
    /// @param entity The entity wich needs to be checked
    /// @return Returns true if the entity is allowed to drop a Bonus and false
    /// if it isn't
    bool canCreateBonus(engine::Entity entity);

    /// @brief This method creates a Bonus at the pos of the dying entity
    /// @param position A copy of the component position of the dying entity
    void createBonus(Component::Position &position);

    /// @brief A ref to a Loot components SparseArray
    SparseArray<Component::Loot> &_loots;
    /// @brief A ref to a Position components SparseArray
    SparseArray<Component::Position> &_positions;
    /// @brief A ref to the registry
    engine::Registry &_reg;
    /// @brief The percentage of chances entities will have to drop a bonus
    float _chancesToDrop;
    std::random_device _rd;
    std::mt19937 _gen;
};

}
#endif /* !R_TYPE_LOOTDROPMANAGER_HPP_ */
