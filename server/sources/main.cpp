#include <iostream>

#include "UdpNetManager.hpp"

int main(int argc, char *argv[])
{
    rtype::UdpNetManager ntm("127.0.0.1", 4242);
    std::vector<rtype::UdpNetManager::Buffer> res;

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
