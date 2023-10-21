/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network server system
*/

#ifndef NETWORKSERVERSYS_HPP_
#define NETWORKSERVERSYS_HPP_

#include "Sync.hpp"

namespace net::system {

class NetworkServer : public Sync {

public:
    NetworkServer(
        engine::Registry &registry, int port,
        std::vector<net::lobby::RemoteClient> const &lobby
    );
    ~NetworkServer() override;

private:
    bool canUpdate(
        net::manager::Client const &client, engine::Entity entity,
        uint8_t component_id, engine::Deserializer deser
    ) override;
};

}

#endif /* NETWORKSERVERSYS_HPP_ */
