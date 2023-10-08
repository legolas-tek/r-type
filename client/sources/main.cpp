#include <iostream>

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
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
        player, Component::Position(0, 0)
    );
    reg.get_components<Component::Position>().insert_at(
        target, Component::Position(0, 0)
    );
    reg.get_components<Component::Velocity>().insert_at(
        player, Component::Velocity(10, 0)
    );
    reg.get_components<Component::Velocity>().insert_at(
        target, Component::Velocity(5, 0)
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
