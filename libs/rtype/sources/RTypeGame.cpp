/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game
*/

#include "IGame.hpp"

#include "Components/Controllable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Components/HitBox.hpp"

#include "Key.hpp"
#include "Rendering.hpp"
#include "Systems/MoveSystem.hpp"

class RTypeGame : public engine::IGame {
public:
    void registerAllComponents(engine::Registry &reg) override
    {
        reg.register_component<Component::Position>();
        reg.register_component<Component::Velocity>();
        reg.register_component<Component::Drawable>();
        reg.register_component<Component::Controllable>();
        reg.register_component<Component::HitBox>();
    }

    void registerAdditionalClientSystems(engine::Registry &reg) override
    {

        reg.add_system<rendering::system::Rendering>(reg);
        reg.add_system<rendering::system::Key>(reg);
    }

    void registerAdditionalSystems(engine::Registry &reg) override
    {
        reg.add_system<System::MoveSystem>(
            reg.get_components<Component::Position>(),
            reg.get_components<Component::Velocity>()
        );
    }

    void initAssets(engine::Registry &reg) override
    {
        reg._assets_paths.push_back(
            "./client/assets/cyberpunk_street_background.png"
        );
        reg._assets_paths.push_back(
            "./client/assets/cyberpunk_street_foreground.png"
        );
    }

    void initScene(engine::Registry &reg) override
    {
        engine::Entity player(1);
        engine::Entity target(2);
        engine::Entity player2(5);

        // set positions
        reg.get_components<Component::Position>().insert_at(
            player, std::move(Component::Position(1, 200))
        );
        reg.get_components<Component::Position>().insert_at(
            target, std::move(Component::Position(1, 250))
        );
        reg.get_components<Component::Position>().insert_at(
            player2, std::move(Component::Position(1, 300))
        );

        // set velocity
        reg.get_components<Component::Velocity>().insert_at(
            player, std::move(Component::Velocity(0, 0))
        );

        // set Drawable
        reg.get_components<Component::Drawable>().insert_at(player, 0);
        reg.get_components<Component::Drawable>().insert_at(player2, 1);

        // set Controllable
        reg.get_components<Component::Controllable>().insert_at(player, 1);
        reg.get_components<Component::Controllable>().insert_at(player2, 1);

        // set hitBox
        reg.get_components<Component::HitBox>().insert_at(player, std::move(Component::HitBox(512.0f, 192.0f)));
        reg.get_components<Component::HitBox>().insert_at(player2, std::move(Component::HitBox(704.0f, 192.0f)));
    }
};
