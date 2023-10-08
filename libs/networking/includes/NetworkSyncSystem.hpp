/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network sync system
*/

#ifndef NETWORKSYNC_HPP_
#define NETWORKSYNC_HPP_

#include "ISystem.hpp"
#include "Registry.hpp"

#include "UdpNetManager.hpp"
#include "Snapshot.hpp"

namespace net::system {

class NetworkServerSync : public ISystem {

public:
    NetworkServerSync(Registry &registry, int port);
    ~NetworkServerSync();

    void operator()();

private:
    Registry &_registry;
    net::manager::Udp _nmu;
};

}

#endif /* NETWORKSYNC_HPP_ */
