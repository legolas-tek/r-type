#include <iostream>

#include "UdpNetManager.hpp"

int main(int argc, char *argv[])
{
    net::manager::Udp ntm(net::server_netmanager, "127.0.0.1", 4242);
    std::vector<net::manager::Udp::Buffer> res;

    while (1) {
        if (not (res = ntm.receive()).empty()) {
            std::cout << res.size() << "packets received" << std::endl;
            net::manager::Udp::Buffer buff(0x01);
            ntm.send(buff);
            res.clear();
            break;
        }
    }
    return 0;
}
