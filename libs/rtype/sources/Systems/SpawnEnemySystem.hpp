/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** SpawnEnemySystem
*/

#ifndef SPAWNENEMYSYSTEM_HPP_
#define SPAWNENEMYSYSTEM_HPP_

#include "Registry.hpp"

#include "ISystem.hpp"

#include <iostream>

#include "Components/Animation.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"

#include "EntityInfo.hpp"

namespace System {

class SpawnEnemySystem : public ISystem {
public:
    SpawnEnemySystem(
        engine::Registry &reg, EntityInfo entityInfo, size_t startTick,
        size_t cycle
    );
    ~SpawnEnemySystem() = default;

    void operator()() override;

    // void addEnemy();

private:
    engine::Registry &_register;
    EntityInfo _entityInfo;
    size_t _startTick;
    size_t _cycle;
    // size_t _waveNum = 0;
    // size_t _createdNum = 0;
    // std::vector<EntityInfo> _entityList;
};
}

#endif /* !SPAWNENEMYSYSTEM_HPP_ */
