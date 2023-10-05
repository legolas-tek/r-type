#include <iostream>

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#include "Components/PositionComponent.hpp"
#include "Components/VelocityComponent.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

#include "Systems/LoggingSystem.hpp"

int main(int argc, char *argv[])
{
    Registry reg;
    Entity background(0);
    Entity player(1);
    Entity target(2);

    reg.register_component<Component::Position>();
    reg.register_component<Component::Velocity>();

    reg.get_components<Component::Position>().insert_at(
        player, std::move(Component::Position(0, std::make_pair(0, 0)))
    );
    reg.get_components<Component::Position>().insert_at(
        target, std::move(Component::Position(1, std::make_pair(0, 0)))
    );
    reg.get_components<Component::Velocity>().insert_at(
        player, std::move(Component::Velocity(0, std::make_pair(10, 0)))
    );
    reg.get_components<Component::Velocity>().insert_at(
        target, std::move(Component::Velocity(1, std::make_pair(0, 10)))
    );

    reg.add_system<System::Logging>(
        reg.get_components<Component::Position>(),
        reg.get_components<Component::Velocity>()
    );

    reg.run_systems();
    reg.run_systems();
    reg.run_systems();

    return 0;
}
