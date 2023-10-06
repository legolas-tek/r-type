#include <iostream>

#include "UdpNetManager.hpp"

int main(int argc, char *argv[])
{
    net::manager::Udp ntm(net::client_netmanager, "127.0.0.1", 4242);
    net::manager::Udp::Buffer buff(1, std::byte('a'));
    std::vector<net::manager::Udp::Buffer> res;

    while (1) {
        try {
            if (ntm.send(buff)) {
                //rtype::UdpNetManager::Buffer &tmp = ntm.getPacket();
                std::cout << "sended" << std::endl;
                //break;
            }
            if (not (res = ntm.receive()).empty()) {
                //rtype::UdpNetManager::Buffer &tmp = ntm.getPacket();
                std::cout << "Halo" << std::endl;
                break;
            }
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}
