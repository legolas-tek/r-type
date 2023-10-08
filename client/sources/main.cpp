#include <iostream>
#include <ciso646>
#include "UdpNetManager.hpp"

int main(int argc, char *argv[])
{
    net::manager::Udp ntm(net::client_netmanager, "127.0.0.1", 4242);
    net::manager::Udp::Buffer buff(10, std::byte('a'));
    std::vector<std::pair<net::manager::Udp::Buffer, net::manager::Udp::Client>> res;
    bool onetime = true;$































                                        

    while (1) {
        try {
            if (onetime) {
                ntm.send(buff);
                onetime = false;
            }
            if (not (res = ntm.receive()).empty()) {
                std::cout << "Packet received" << std::endl;
                break;
            }
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}
