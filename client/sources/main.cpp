#include <iostream>

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

// #include "Components/PositionComponent.hpp"
// #include "Components/VelocityComponent.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

#include "Rendering.hpp"
#include "Render2dEntity.hpp"
#include "Render3dEntity.hpp"

#include "Systems/LoggingSystem.hpp"
#include "UdpNetManager.hpp"

int main(int argc, char *argv[])
{
    engine::Registry reg;
    engine::Entity player(1);
    engine::Entity target(2);

    reg._assets_paths.push_back("./client/assets/cyberpunk_street_background.png");

    reg.register_component<Component::Position>();
    reg.register_component<Component::Velocity>();
    reg.register_component<Component::Drawable>();

    reg.get_components<Component::Position>().insert_at(
        player, std::move(Component::Position(1, 200))
    );
    reg.get_components<Component::Position>().insert_at(
        target, std::move(Component::Position(1, 500))
    );
    reg.get_components<Component::Velocity>().insert_at(
        player, std::move(Component::Velocity(5, 0))
    );
    reg.get_components<Component::Velocity>().insert_at(
        target, std::move(Component::Velocity(10, 0))
    );
    reg.get_components<Component::Drawable>().insert_at(
        player, 0
    );

    reg.add_system<System::Logging>(
        reg.get_components<Component::Position>(),
        reg.get_components<Component::Velocity>()
    );

    reg.add_system<rendering::Rendering>(reg);

    reg.run_systems();
    // rendering::Rendering window;
    // Render2dEntity entity2d(std::string("./client/assets/cyberpunk_street_background.png"));
    // Render3dEntity entity3d("./client/assets/SU-27.obj", "./client/assets/BODYMAINCOLORCG.png");

    // window.addEntity(std::make_unique<Render2dEntity>("./client/assets/cyberpunk_street_foreground.png"));

    // entity2d.setScale(2.0f);

    // BoundingBox box = GetMeshBoundingBox(entity3d.getModel().meshes[0]);
    // std::cout << "max " << " x: " << box.max.x << " y: " << box.max.y << " z: " << box.max.z << std::endl;
    // std::cout << "min " << " x: " << box.min.x << " y: " << box.min.y << " z: " << box.min.z << std::endl;

    // window.setCameraPos(00.0f, (box.max.y - box.min.y) / 2, 30.0f);
    // // window.setCameraPos((box.max.x - box.min.x) / 2, (box.max.y - box.min.y) / 2, 20.0f);
    // window.setCameraTarget(0.0f, 0.0f, 0.0f);
    // // window.setCameraTarget((box.max.x - box.min.x) / 2, (box.max.y - box.min.y) / 2, 0.0f);
    // window.setCameraUp(0.0f, 1.0f, 0.0f);
    // window.setCameraFovy(45.0f);

    // Ray ray = { 0 };

    // while (!WindowShouldClose()) {
    //     BeginDrawing();
    //         ClearBackground(RAYWHITE);
    //     EndDrawing();
    //     // window.beginDrawing();
    //     // window.drawBackgroundColor();
    //     // entity2d.drawEntity();
    //     // window.entities[0]->drawEntity();
    //     // window.beginDrawing3d();
    //     //     entity3d.drawEntity();
    //     //     DrawGrid(10, 10.0f);
    //     // window.endDrawing3d();
    //     // window.endDrawing();
    // }
}
