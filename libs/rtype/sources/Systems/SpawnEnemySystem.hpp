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

#include <random>

#include "Components/Animation.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"

#include "EntityInfo.hpp"

namespace System {

class SpawnEnemySystem : public ISystem {
public:
    SpawnEnemySystem(
        engine::Registry &reg, EntityInfo entityInfo, size_t startTick,
        size_t cycle, int minX, int maxX, int minY, int maxY
    );
    ~SpawnEnemySystem() override = default;

    void operator()() override;

    // void addEnemy();

private:
    engine::Registry &_register;
    EntityInfo _entityInfo;
    size_t _startTick;
    size_t _cycle;
    int _minX;
    int _maxX;
    int _minY;
    int _maxY;

    std::random_device rd;
    std::mt19937 _gen;
};
}

#endif /* !SPAWNENEMYSYSTEM_HPP_ */
