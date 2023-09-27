#include <iostream>

#include "Entity.hpp"
#include "NetManager.hpp"

int main(int argc, char *argv[])
{
    Entity entity(2);
    NetManager net;
    std::cout << "Welcome to the R-Type server." << std::endl;
    return 0;
}
