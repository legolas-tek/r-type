/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network client system
*/

#ifndef NETWORKCLIENTSYS_HPP_
#define NETWORKCLIENTSYS_HPP_

#include "Registry.hpp"

#include "Sync.hpp"

namespace net::system {

class NetworkClient : public Sync {

public:
    NetworkClient(
        engine::Registry &registry, std::string const &addr, int port,
        size_t playerNumber, size_t playerHash
    );
    ~NetworkClient() override;
};

}

#endif /* NETWORKCLIENTSYS_HPP_ */
