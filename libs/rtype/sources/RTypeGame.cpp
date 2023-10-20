/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game
*/

#include "Game.hpp"

#include "Components/Animation.hpp"
#include "Components/Collision.hpp"
#include "Components/Controllable.hpp"
#include "Components/Damage.hpp"
#include "Components/Drawable.hpp"
#include "Components/FireRate.hpp"
#include "Components/HitBox.hpp"
#include "Components/Life.hpp"
#include "Components/LifeTime.hpp"
#include "Components/Position.hpp"
#include "Components/Text.hpp"
#include "Components/Velocity.hpp"

#include "Systems/AnimationSystem.hpp"
#include "Systems/AttackSystem.hpp"
#include "Systems/CollisionsSystem.hpp"
#include "Systems/DamageSystem.hpp"
#include "Systems/LifeTimeSystem.hpp"
#include "Systems/MoveSystem.hpp"
#include "Systems/NetworkSystem.hpp"
#include "Systems/SpawnEnemySystem.hpp"
#include "Systems/WaveManagerSystem.hpp"

#include "Key.hpp"
#include "NetworkClientSystem.hpp"
#include "Rendering.hpp"

void RTypeGame::registerAllComponents(engine::Registry &reg)
{
    reg.register_component<Component::Position>();
    reg.register_component<Component::Velocity>();
    reg.register_component<Component::Drawable>();
    reg.register_component<Component::Controllable>();
    reg.register_component<Component::Collision>();
    reg.register_component<Component::Animation>();
    reg.register_component<Component::HitBox>();
    reg.register_component<Component::FireRate>();
    reg.register_component<Component::LifeTime>();
    reg.register_component<Component::Damage>();
    reg.register_component<Component::Life>();
    reg.register_component<Component::Text>();
}

void RTypeGame::registerAdditionalServerSystems(engine::Registry &reg)
{
    reg.add_system<System::AttackSystem>(
        reg.get_components<Component::FireRate>(), reg
    );
    reg.add_system<System::LifeTimeSystem>(
        reg.get_components<Component::LifeTime>(), reg
    );
    reg.add_system<System::DamageSystem>(
        reg.get_components<Component::Damage>(),
        reg.get_components<Component::Life>(),
        reg.get_components<Component::Collision>(), reg
    );
    reg.add_system<System::CollisionsSystem>(
        reg.get_components<Component::Position>(),
        reg.get_components<Component::HitBox>(),
        reg.get_components<Component::Collision>()
    );
    reg.add_system<rtype::NetworkServerSystem>(reg, 4242);
}

void RTypeGame::registerAdditionalClientSystems(engine::Registry &reg)
{
    reg.add_system<System::AnimationSystem>(reg);
    reg.add_system<System::WaveManagerSystem>(reg);
    reg.add_system<rendering::system::Rendering>(reg);
    reg.add_system<rendering::system::Key>(reg);
    reg.add_system<net::system::NetworkClient>(reg, 4242);
}

void RTypeGame::registerAdditionalSystems(engine::Registry &reg)
{
    reg.add_system<System::MoveSystem>(
        reg.get_components<Component::Position>(),
        reg.get_components<Component::Velocity>()
    );
}

void RTypeGame::initAssets(engine::Registry &reg)
{
    reg._assets_paths.emplace_back(
        "./client/assets/images/cyberpunk_street_background.png"
    );
    reg._assets_paths.emplace_back(
        "./client/assets/images/cyberpunk_street_midground.png"
    );
    reg._assets_paths.emplace_back(
        "./client/assets/images/cyberpunk_street_foreground.png"
    );
    reg._assets_paths.push_back("./client/assets/scarfy.png");
    reg._assets_paths.push_back("./client/assets/Plasma_Beam.png");
    reg._assets_paths.push_back("./client/assets/mutalisk.png");
    reg._assets_paths.push_back("./client/assets/scourge.png");
}

void RTypeGame::initScene(engine::Registry &reg)
{
    engine::Entity background(reg.get_new_entity());
    engine::Entity midground(reg.get_new_entity());
    engine::Entity foreground(reg.get_new_entity());
    engine::Entity scarfy(reg.get_new_entity());
    engine::Entity dummy(reg.get_new_entity());
    engine::Entity Title(reg.get_new_entity());

    // ==================== set positions ====================
    // background
    reg.get_components<Component::Position>().insert_at(
        background, Component::Position(0, 0, 0)
    );
    // midground
    reg.get_components<Component::Position>().insert_at(
        midground, Component::Position(0, 0, 0)
    );
    // foreground
    reg.get_components<Component::Position>().insert_at(
        foreground, Component::Position(0, 0, 0)
    );
    // player
    reg.get_components<Component::Position>().insert_at(
        scarfy, Component::Position(150, 150, 1)
    );
    // test dummy
    reg.get_components<Component::Position>().insert_at(
        dummy, Component::Position(500, 150, 1)
    );
    // title
    reg.get_components<Component::Position>().insert_at(
        Title, Component::Position(50, 50, 0)
    );

    // ==================== set velocity ====================
    reg.get_components<Component::Velocity>().insert_at(
        scarfy, Component::Velocity()
    );
    // ==================== set Drawable ====================
    // background
    reg.get_components<Component::Drawable>().insert_at(
        background, Component::Drawable(0, 512.0f, 192.0f, 2.0f)
    );
    // midground
    reg.get_components<Component::Drawable>().insert_at(
        midground, Component::Drawable(1, 512.0f, 192.0f, 2.0f)
    );
    // foreground
    reg.get_components<Component::Drawable>().insert_at(
        foreground, Component::Drawable(2, 512.0f, 192.0f, 2.0f)
    );
    // player
    reg.get_components<Component::Drawable>().insert_at(
        scarfy, Component::Drawable(3, 128.0f, 128.0f, 1.0f)
    );
    // test dummy
    reg.get_components<Component::Drawable>().insert_at(
        dummy, Component::Drawable(3, 128.0f, 128.0f, 1.0f)
    );

    // ==================== set Animation ====================
    reg.get_components<Component::Animation>().insert_at(
        background, Component::Animation(1024, 192, 512, 192, 1, 1)
    );
    reg.get_components<Component::Animation>().insert_at(
        midground, Component::Animation(1024, 192, 512, 192, 3, 1)
    );
    reg.get_components<Component::Animation>().insert_at(
        foreground, Component::Animation(1408, 192, 704, 192, 5, 1)
    );
    reg.get_components<Component::Animation>().insert_at(
        scarfy, Component::Animation(768, 128, 128, 128, 128, 10)
    );

    // // ==================== set Controllable ====================
    reg.get_components<Component::Controllable>().insert_at(scarfy, 2);

    // ==================== set Collision ====================
    reg.get_components<Component::Collision>().insert_at(
        scarfy, Component::Collision(128, 128)
    );
    reg.get_components<Component::Collision>().insert_at(
        dummy, Component::Collision(128, 128)
    );

    // ==================== set FireRate ====================
    reg.get_components<Component::FireRate>().insert_at(
        scarfy, Component::FireRate(50)
    );

    // ==================== set LifeTime ====================
    // register you're LifeTime components

    // ==================== set Life ========================
    reg.get_components<Component::Life>().insert_at(dummy, Component::Life(10));

    // ==================== set Text ====================
    reg.get_components<Component::Text>().insert_at(
        Title,
        std::move(Component::Text(
            "R-Type", "./client/assets/fonts/Over_There.ttf", 50, 10
        ))
    );
}

std::unique_ptr<engine::IGame> RTypeGame::createLobby()
{
    // TODO: fix the lobby before changing this line
    // return std::make_unique<RTypeLobby>();
    return nullptr;
}

engine::IGame *createGame()
{
    return new RTypeGame();
}
