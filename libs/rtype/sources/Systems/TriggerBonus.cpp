/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** TriggerBonus
*/

#include "Systems/TriggerBonus.hpp"
#include "Game.hpp"
#include "Systems/AttackSystem.hpp"

#include "Events/Collision.hpp"
#include "Events/Death.hpp"

#include "Components/FireRate.hpp"
#include "Components/Follow.hpp"
#include "Components/LifeTime.hpp"
#include "Components/Position.hpp"

System::TriggerBonus::TriggerBonus(
    SparseArray<Component::Bonus> &bonuses,
    SparseArray<Component::Controllable> &controllables,
    SparseArray<Component::Life> &lifes, engine::Registry &reg
)
    : _bonuses(bonuses)
    , _controllables(controllables)
    , _lifes(lifes)
    , _reg(reg)
{
}

void System::TriggerBonus::operator()()
{
    for (auto &collision : _reg.events.getEvents<event::Collision>()) {
        if (_bonuses[collision.secondEntity]
            and _controllables[collision.entity]) {
            processBonus(collision.entity, collision.secondEntity);
        }
    }
}

void System::TriggerBonus::processBonus(
    engine::Entity player, engine::Entity bonus
)
{
    Component::Bonus::BonusTypes bonusType = _bonuses[bonus]->bonusType;

    if (bonusType == Component::Bonus::WEAPON) {
        createExtrasCannons(player);
    }
    if (bonusType == Component::Bonus::LIFE && _lifes[player]) {
        _lifes[player]->lifes += 1;
    }
    _reg.events.addEvent<event::Death>(bonus);
}

void System::TriggerBonus::createExtrasCannons(engine::Entity player)
{
    engine::Entity upCannon(_reg.get_new_entity());
    engine::Entity downCannon(_reg.get_new_entity());

    _reg.get_components<Component::Position>().emplace_at(upCannon, 0, 0);
    _reg.get_components<Component::Position>().emplace_at(downCannon, 0, 0);
    _controllables.emplace_at(upCannon);
    _controllables.emplace_at(downCannon);
    _reg.get_components<Component::LifeTime>().emplace_at(
        upCannon, 1000, _reg.getTick()
    );
    _reg.get_components<Component::LifeTime>().emplace_at(
        downCannon, 1000, _reg.getTick()
    );
    _reg.get_components<Component::Follow>().emplace_at(
        upCannon, player,
        RTypeGame::SHIP_W / 2 + System::AttackSystem::LASER_WIDTH + 1,
        -(RTypeGame::SHIP_H / 2)
    );
    _reg.get_components<Component::Follow>().emplace_at(
        downCannon, player,
        RTypeGame::SHIP_W / 2 + System::AttackSystem::LASER_WIDTH + 1,
        RTypeGame::SHIP_H / 2
    );
    _reg.get_components<Component::FireRate>().emplace_at(
        upCannon, RTypeGame::SHIP_FIRE_RATE
    );
    _reg.get_components<Component::FireRate>().emplace_at(
        upCannon, RTypeGame::SHIP_FIRE_RATE
    );
}
