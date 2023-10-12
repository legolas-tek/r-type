/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Client class of the net namespace
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <asio.hpp>

#include "Net.hpp"

namespace net::manager {

class Client {

public:
    Client(asio::ip::udp::endpoint const &endpoint)
        : _endpoint(endpoint)
    {
    }

    ~Client() = default;

    asio::ip::udp::endpoint getEndpoint() const
    {
        return _endpoint;
    }

private:
    asio::ip::udp::endpoint _endpoint;
};

}

#endif /* CLIENT_HPP_ */
