/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** LootDropManager
*/

#include "Systems/LootDropManager.hpp"
#include "Systems/WaveManagerSystem.hpp"
#include "Game.hpp"

#include "Events/Death.hpp"

#include "Components/Drawable.hpp"
#include "Components/Animation.hpp"
#include "Components/Collision.hpp"
#include "Components/HitBox.hpp"
#include "Components/Bonus.hpp"
#include "Components/LifeTime.hpp"

System::LootDropManager::LootDropManager(
    SparseArray<Component::Loot> &loots,
    SparseArray<Component::Position> &positions, engine::Registry &reg,
    int chancesToDrop
)
    : _loots(loots)
    , _positions(positions)
    , _reg(reg)
    , _chancesToDrop(chancesToDrop)
    , _gen(_rd())
{
}

void System::LootDropManager::operator()()
{
    for (auto &death : _reg.events.getEvents<event::Death>()) {
        if (_loots[death.entity] && canCreateBonus(death.entity)) {
            createBonus(_positions[death.entity].value());
        }
    }
}

bool System::LootDropManager::canCreateBonus(engine::Entity entity)
{
    if (not _positions[entity])
        return false;
    std::uniform_real_distribution<float> distrib(0, 100);
    float random = distrib(_gen);

    return random <= _chancesToDrop;
}

void System::LootDropManager::createBonus(Component::Position &position)
{
    engine::Entity bonus(_reg.get_new_entity());
    std::uniform_real_distribution<float> distrib(0, 2);
    float random = distrib(_gen);

    _reg.get_components<Component::Position>().emplace_at(
        bonus, position._x, position._y, -1
    );
    _reg.get_components<Component::Drawable>().emplace_at(
        bonus, RTypeGame::BONUS_I, RTypeGame::BONUS_W, RTypeGame::BONUS_H, 0.15
    );
    _reg.get_components<Component::Animation>().emplace_at(
        bonus, RTypeGame::BONUS_W * RTypeGame::BONUS_F, RTypeGame::BONUS_H,
        RTypeGame::BONUS_W, RTypeGame::BONUS_H, RTypeGame::BONUS_W, 10
    );
    _reg.get_components<Component::Bonus>().emplace_at(
        bonus, Component::Bonus::BonusTypes(random)
    );
    _reg.get_components<Component::HitBox>().emplace_at(
        bonus, RTypeGame::BONUS_W * 0.15, RTypeGame::BONUS_H * 0.15
    );
    _reg.get_components<Component::Collision>().emplace_at(
        bonus, RTypeGame::BONUS_W * 0.15, RTypeGame::BONUS_H * 0.15
    );
    _reg.get_components<Component::LifeTime>().emplace_at(
        bonus, System::secondsToTick(5), _reg.getTick()
    );
}
