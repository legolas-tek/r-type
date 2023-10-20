/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game-specific network system
*/

#ifndef R_TYPE_NETWORKSYSTEM_HPP
#define R_TYPE_NETWORKSYSTEM_HPP

#include "NetworkServerSystem.hpp"

namespace rtype {

class NetworkServerSystem : public net::system::NetworkServer {
public:
    using net::system::NetworkServer::NetworkServer;

private:
    bool canUpdate(
        engine::Entity entity, uint8_t component_id, engine::Deserializer deser
    ) override;
};

}

#endif /* !R_TYPE_NETWORKSYSTEM_HPP */
