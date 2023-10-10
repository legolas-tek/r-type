#include "Registry.hpp"

#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Systems/LoggingSystem.hpp"

#include "NetworkServerSystem.hpp"

int main(int argc, char *argv[])
{
    engine::Registry reg;
    engine::Entity player(1);
    engine::Entity target(2);

    reg.register_component<Component::Position>();
    reg.register_component<Component::Velocity>();
    reg.get_components<Component::Position>().insert_at(player,
        std::move(Component::Position(1, 200)));
    reg.get_components<Component::Position>().insert_at(target,
        std::move(Component::Position(1, 500)));
    reg.get_components<Component::Velocity>().insert_at(player,
        std::move(Component::Velocity(5, 0)));
    reg.get_components<Component::Velocity>().insert_at(target,
        std::move(Component::Velocity(10, 0)));
    reg.add_system<System::Logging>(reg.get_components<Component::Position>(),
        reg.get_components<Component::Velocity>());
    reg.add_system<net::system::NetworkServer>(reg, 4242);

    while (1)
        reg.run_systems();

    //net::manager::Udp ntm(net::server_netmanager, "127.0.0.1", 4242);
    //std::vector<std::pair<net::manager::Udp::Buffer, net::manager::Udp::Client>> res;

    //while (1) {
        //if (not (res = ntm.receive()).empty()) {
            //std::cout << res.size() << "packets received" << std::endl;
            //net::manager::Udp::Buffer buff(0x01);
            //ntm.send(buff);
            //res.clear();
            //break;
        //}
    //}
    return 0;
}
