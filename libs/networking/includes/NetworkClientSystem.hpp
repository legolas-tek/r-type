/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network client system
*/

#ifndef NETWORKCLIENTSYS_HPP_
#define NETWORKCLIENTSYS_HPP_

#include <unordered_map>

#include "Registry.hpp"

#include "UdpNetManager.hpp"
#include "Snapshot.hpp"

#include "Sync.hpp"

namespace net::system {

class NetworkClient : public Sync {

public:
    NetworkClient(engine::Registry &registry, int port);
    ~NetworkClient();

};

}

#endif /* NETWORKCLIENTSYS_HPP_ */
