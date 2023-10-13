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
#include "Components/Collision.hpp"
#include "Components/Parallax.hpp"
#include "Components/Animation.hpp"

#include "Key.hpp"
#include "Rendering.hpp"
#include "Systems/MoveSystem.hpp"
#include "Systems/ParallaxSystem.hpp"
#include "Systems/AnimationSystem.hpp"

class RTypeGame : public engine::IGame {
public:
    void registerAllComponents(engine::Registry &reg) override
    {
        reg.register_component<Component::Position>();
        reg.register_component<Component::Velocity>();
        reg.register_component<Component::Drawable>();
        reg.register_component<Component::Controllable>();
        reg.register_component<Component::Collision>();
        reg.register_component<Component::Parallax>();
        reg.register_component<Component::Animation>();
    }

    void registerAdditionalClientSystems(engine::Registry &reg) override
    {

        reg.add_system<System::ParallaxSystem>(reg);
        reg.add_system<System::AnimationSystem>(reg);
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
        reg._assets_paths.push_back(
            "./client/assets/scarfy.png"
        );
    }

    void initScene(engine::Registry &reg) override
    {
        engine::Entity background_1(1);
        engine::Entity background_2(2);
        engine::Entity scarfy(3);

        // set positions
        reg.get_components<Component::Position>().insert_at(
            background_1, std::move(Component::Position(0, 0))
        );
        reg.get_components<Component::Position>().insert_at(
            background_2, std::move(Component::Position(1024, 0))
        );
        reg.get_components<Component::Position>().insert_at(
            scarfy, std::move(Component::Position(100, 100))
        );

        // set velocity
        reg.get_components<Component::Velocity>().insert_at(
            background_1, std::move(Component::Velocity(-1.0f, 0))
        );
        reg.get_components<Component::Velocity>().insert_at(
            background_2, std::move(Component::Velocity(-1.0f, 0))
        );

        // set Drawable
        reg.get_components<Component::Drawable>().insert_at(
            background_1, std::move(Component::Drawable(0, 512.0f, 192.0f, 2.0f))
        );
        reg.get_components<Component::Drawable>().insert_at(
            background_2, std::move(Component::Drawable(0, 512.0f, 192.0f, 2.0f))
        );
        reg.get_components<Component::Drawable>().insert_at(
            scarfy, std::move(Component::Drawable(2, 128.0f, 128.0f, 1.0f))
        );

        // set Parallax
        reg.get_components<Component::Parallax>().insert_at(
            background_1, std::move(Component::Parallax(0.0f, 0.0f))
        );
        reg.get_components<Component::Parallax>().insert_at(
            background_2, std::move(Component::Parallax(1024.0f, 0.0f))
        );

        // set Animation
        reg.get_components<Component::Animation>().insert_at(
            scarfy, std::move(Component::Animation(6))
        );


        // // set Controllable
        // reg.get_components<Component::Controllable>().insert_at(background_1, 1);
        // reg.get_components<Component::Controllable>().insert_at(player2, 1);

        // // set Collision
        // reg.get_components<Component::Collision>().insert_at(player, std::move(Component::Collision(512.0f, 192.0f)));
        // reg.get_components<Component::Collision>().insert_at(player2, std::move(Component::Collision(704.0f, 192.0f)));
    }
};
