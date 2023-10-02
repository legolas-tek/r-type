#include <iostream>

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#include "Registry.hpp"
#include "Entity.hpp"
#include "position.hpp"
#include "velocity.hpp"

#include "Logging_system.hpp"

int main(int argc, char *argv[])
{
    Registry reg;
    Entity background(0);
    Entity player(1);
    Entity target(2);

    reg.register_component<Component::position>();
    reg.register_component<Component::velocity>();

    reg.get_components<Component::position>().insert_at(player, std::move(Component::position(1, 200)));
    reg.get_components<Component::position>().insert_at(target, std::move(Component::position(1, 500)));
    reg.get_components<Component::velocity>().insert_at(player, std::move(Component::velocity(5, 0)));
    reg.get_components<Component::velocity>().insert_at(target, std::move(Component::velocity(10, 0)));

    reg.add_system<System::Logging>(reg.get_components<Component::position>(), reg.get_components<Component::velocity>());

    reg.run_systems();
    reg.run_systems();
    reg.run_systems();

    return 0;
}
