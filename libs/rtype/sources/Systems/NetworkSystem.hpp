/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game-specific network system
*/

#ifndef R_TYPE_NETWORKSYSTEM_HPP
#define R_TYPE_NETWORKSYSTEM_HPP

#include "NetworkClientSystem.hpp"
#include "NetworkServerSystem.hpp"

namespace rtype {

class NetworkServerSystem : public net::system::NetworkServer {
public:
    using net::system::NetworkServer::NetworkServer;

private:
    bool canUpdate(
        net::manager::Client const &client, engine::Entity entity,
        uint8_t component_id, engine::Deserializer deser
    ) override;
};

class NetworkClientSystem : public net::system::NetworkClient {
public:
    using net::system::NetworkClient::NetworkClient;

private:
    bool canSend(
        std::size_t clientNumber, engine::Entity entity, uint8_t component_id
    ) override;
};
}

#endif /* !R_TYPE_NETWORKSYSTEM_HPP */
