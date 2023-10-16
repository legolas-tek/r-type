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
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

#include "Key.hpp"
#include "Rendering.hpp"
#include "Systems/AnimationSystem.hpp"
#include "Systems/MoveSystem.hpp"

#include "NetworkClientSystem.hpp"
#include "NetworkSystem.hpp"

class RTypeGame : public engine::IGame {
public:
    void registerAllComponents(engine::Registry &reg) override
    {
        reg.register_component<Component::Position>();
        reg.register_component<Component::Velocity>();
        reg.register_component<Component::Drawable>();
        reg.register_component<Component::Controllable>();
        reg.register_component<Component::Collision>();
        reg.register_component<Component::Animation>();
    }

    void registerAdditionalServerSystems(engine::Registry &reg) override
    {
        reg.add_system<rtype::NetworkServerSystem>(reg, 4242);
    }

    void registerAdditionalClientSystems(engine::Registry &reg) override
    {
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
        engine::Entity background(1);
        engine::Entity midground(3);
        engine::Entity foreground(6);
        engine::Entity scarfy(7);

        // ==================== set positions ====================
        // background
        reg.get_components<Component::Position>().insert_at(
            background, std::move(Component::Position(0, 0))
        );
        // midground
        reg.get_components<Component::Position>().insert_at(
            midground, std::move(Component::Position(0, 0))
        );
        // foreground
        reg.get_components<Component::Position>().insert_at(
            foreground, std::move(Component::Position(0, 0))
        );
        // player
        reg.get_components<Component::Position>().insert_at(
            scarfy, std::move(Component::Position(100, 100))
        );

        // ==================== set velocity ====================
        reg.get_components<Component::Velocity>().insert_at(
            scarfy, std::move(Component::Velocity())
        );
        // ==================== set Drawable ====================
        // background
        reg.get_components<Component::Drawable>().insert_at(
            background, std::move(Component::Drawable(0, 512.0f, 192.0f, 2.0f))
        );
        // midground
        reg.get_components<Component::Drawable>().insert_at(
            midground, std::move(Component::Drawable(1, 512.0f, 192.0f, 2.0f))
        );
        // foreground
        reg.get_components<Component::Drawable>().insert_at(
            foreground, std::move(Component::Drawable(2, 512.0f, 192.0f, 2.0f))
        );

        // player
        reg.get_components<Component::Drawable>().insert_at(
            scarfy, std::move(Component::Drawable(3, 128.0f, 128.0f, 1.0f))
        );

        // ==================== set Animation ====================
        reg.get_components<Component::Animation>().insert_at(
            background, std::move(Component::Animation(1024, 192, 512, 192, 1))
        );
        reg.get_components<Component::Animation>().insert_at(
            midground, std::move(Component::Animation(1024, 192, 512, 192, 3))
        );
        reg.get_components<Component::Animation>().insert_at(
            foreground, std::move(Component::Animation(1408, 192, 704, 192, 5))
        );
        reg.get_components<Component::Animation>().insert_at(
            scarfy, std::move(Component::Animation(768, 128, 128, 128, 128))
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

engine::IGame *createGame()
{
    return new RTypeGame();
}
