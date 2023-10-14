/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game
*/

#include "IGame.hpp"

#include "Components/Animation.hpp"
#include "Components/Collision.hpp"
#include "Components/Controllable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Parallax.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

#include "Key.hpp"
#include "Rendering.hpp"
#include "Systems/AnimationSystem.hpp"
#include "Systems/MoveSystem.hpp"
#include "Systems/ParallaxSystem.hpp"

#include "NetworkServerSystem.hpp"
#include "NetworkClientSystem.hpp"

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

    void registerAdditionalServerSystems(engine::Registry &reg) override
    {
        reg.add_system<net::system::NetworkServer>(reg, 4242);
    }


    void registerAdditionalClientSystems(engine::Registry &reg) override
    {

        reg.add_system<System::ParallaxSystem>(reg);
        reg.add_system<System::AnimationSystem>(reg);
        reg.add_system<rendering::system::Rendering>(reg);
        reg.add_system<rendering::system::Key>(reg);
        reg.add_system<net::system::NetworkClient>(reg, 4242);
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
            "./client/assets/cyberpunk_street_midground.png"
        );
        reg._assets_paths.push_back(
            "./client/assets/cyberpunk_street_foreground.png"
        );
        reg._assets_paths.push_back("./client/assets/scarfy.png");
    }

    void initScene(engine::Registry &reg) override
    {
        engine::Entity background_1(1);
        engine::Entity background_2(2);
        engine::Entity midground_1(3);
        engine::Entity midground_2(4);
        engine::Entity foreground_1(5);
        engine::Entity foreground_2(6);
        engine::Entity scarfy(7);

        // ==================== set positions ====================
        // background
        reg.get_components<Component::Position>().insert_at(
            background_1, std::move(Component::Position(0, 0))
        );
        reg.get_components<Component::Position>().insert_at(
            background_2, std::move(Component::Position(1024, 0))
        );
        // midground
        reg.get_components<Component::Position>().insert_at(
            midground_1, std::move(Component::Position(0, 0))
        );
        reg.get_components<Component::Position>().insert_at(
            midground_2, std::move(Component::Position(1024, 0))
        );
        // foreground
        reg.get_components<Component::Position>().insert_at(
            foreground_1, std::move(Component::Position(0, 0))
        );
        reg.get_components<Component::Position>().insert_at(
            foreground_2, std::move(Component::Position(1024, 0))
        );
        // player
        reg.get_components<Component::Position>().insert_at(
            scarfy, std::move(Component::Position(100, 100))
        );

        // ==================== set velocity ====================
        // background
        reg.get_components<Component::Velocity>().insert_at(
            background_1, std::move(Component::Velocity(-1.0f, 0))
        );
        reg.get_components<Component::Velocity>().insert_at(
            background_2, std::move(Component::Velocity(-1.0f, 0))
        );
        // midground
        reg.get_components<Component::Velocity>().insert_at(
            midground_1, std::move(Component::Velocity(-3.0f, 0))
        );
        reg.get_components<Component::Velocity>().insert_at(
            midground_2, std::move(Component::Velocity(-3.0f, 0))
        );
        // foreground
        reg.get_components<Component::Velocity>().insert_at(
            foreground_1, std::move(Component::Velocity(-5.0f, 0))
        );
        reg.get_components<Component::Velocity>().insert_at(
            foreground_2, std::move(Component::Velocity(-5.0f, 0))
        );

        // ==================== set Drawable ====================
        // background
        reg.get_components<Component::Drawable>().insert_at(
            background_1,
            std::move(Component::Drawable(0, 512.0f, 192.0f, 2.0f))
        );
        reg.get_components<Component::Drawable>().insert_at(
            background_2,
            std::move(Component::Drawable(0, 512.0f, 192.0f, 2.0f))
        );
        // midground
        reg.get_components<Component::Drawable>().insert_at(
            midground_1, std::move(Component::Drawable(1, 512.0f, 192.0f, 2.0f))
        );
        reg.get_components<Component::Drawable>().insert_at(
            midground_2, std::move(Component::Drawable(1, 512.0f, 192.0f, 2.0f))
        );
        // foreground
        reg.get_components<Component::Drawable>().insert_at(
            foreground_1,
            std::move(Component::Drawable(2, 512.0f, 192.0f, 2.0f))
        );
        reg.get_components<Component::Drawable>().insert_at(
            foreground_2,
            std::move(Component::Drawable(2, 512.0f, 192.0f, 2.0f))
        );
        // player
        reg.get_components<Component::Drawable>().insert_at(
            scarfy, std::move(Component::Drawable(3, 128.0f, 128.0f, 1.0f))
        );

        // ==================== set Parallax ====================
        // background
        reg.get_components<Component::Parallax>().insert_at(
            background_1, std::move(Component::Parallax(0.0f, 0.0f))
        );
        reg.get_components<Component::Parallax>().insert_at(
            background_2, std::move(Component::Parallax(1024.0f, 0.0f))
        );
        // midground
        reg.get_components<Component::Parallax>().insert_at(
            midground_1, std::move(Component::Parallax(0.0f, 0.0f))
        );
        reg.get_components<Component::Parallax>().insert_at(
            midground_2, std::move(Component::Parallax(1024.0f, 0.0f))
        );
        // foreground
        reg.get_components<Component::Parallax>().insert_at(
            foreground_1, std::move(Component::Parallax(0.0f, 0.0f))
        );
        reg.get_components<Component::Parallax>().insert_at(
            foreground_2, std::move(Component::Parallax(1024.0f, 0.0f))
        );

        // ==================== set Animation ====================
        reg.get_components<Component::Animation>().insert_at(
            scarfy, std::move(Component::Animation(6))
        );

        // // ==================== set Controllable ====================
        reg.get_components<Component::Controllable>().insert_at(scarfy, 2);
        // reg.get_components<Component::Controllable>().insert_at(player2, 1);

        // // ==================== set Collision ====================
        // reg.get_components<Component::Collision>().insert_at(player,
        // std::move(Component::Collision(512.0f, 192.0f)));
        // reg.get_components<Component::Collision>().insert_at(player2,
        // std::move(Component::Collision(704.0f, 192.0f)));
    }
};
