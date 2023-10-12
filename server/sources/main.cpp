#include "Registry.hpp"

#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Systems/LoggingSystem.hpp"

#include "NetworkServerSystem.hpp"

#include "UdpNetManager.hpp"

int main(int argc, char *argv[])
{
    engine::Registry reg;
    engine::Entity player(1);
    engine::Entity target(2);

    reg.register_component<Component::Position>();
    reg.register_component<Component::Velocity>();
    reg.get_components<Component::Position>().insert_at(player,
        std::move(Component::Position(1, 200)));
    reg.get_components<Component::Velocity>().insert_at(player,
        std::move(Component::Velocity(1, 2)));
    reg.get_components<Component::Velocity>().insert_at(target,
        std::move(Component::Velocity(3, 4)));
    reg.add_system<System::Logging>(reg.get_components<Component::Position>(),
        reg.get_components<Component::Velocity>());
    reg.add_system<net::system::NetworkServer>(reg, 4242);

    while (1)
        reg.run_systems();

    return 0;
}
