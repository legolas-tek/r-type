#include <iostream>

#include "UdpNetManager.hpp"

int main(int argc, char *argv[])
{
    net::manager::Udp ntm(net::server_netmanager, "127.0.0.1", 4242);
    std::vector<net::manager::Udp::Buffer> res;

    while (1) {
        try {
            if (not (res = ntm.receive()).empty()) {
                std::cout << res.back().size() << std::endl;
                break;
            }
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}
