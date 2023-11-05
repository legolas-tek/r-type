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
        size_t cycle, float minX, float maxX, float minY, float maxY
    );

    void operator()() override;

private:
    engine::Registry &_register;
    EntityInfo _entityInfo;
    size_t _startTick;
    size_t _cycle;
    float _minX;
    float _maxX;
    float _minY;
    float _maxY;

    std::random_device rd;
    std::mt19937 _gen;
};
}

#endif /* !SPAWNENEMYSYSTEM_HPP_ */
