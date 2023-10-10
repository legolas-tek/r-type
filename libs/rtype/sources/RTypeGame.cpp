/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game
*/

#include "IGame.hpp"
#include "Registry.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Components/Drawable.hpp"
#include "Components/HitBox.hpp"
#include "Components/Collision.hpp"
#include "Components/Life.hpp"
#include "Components/Controllable.hpp"

class RTypeGame : public engine::IGame {
public:
    void registerAllComponents(engine::Registry &reg) override
    {
        using namespace Component;
        reg.register_component<Position>();
        reg.register_component<Velocity>();
        reg.register_component<Drawable>();
        reg.register_component<HitBox>();
        reg.register_component<Collision>();
        reg.register_component<Life>();
        reg.register_component<Controllable>();
    }
};
