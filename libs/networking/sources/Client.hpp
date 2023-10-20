/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Client class of the net namespace
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <asio.hpp>
#include <utility>

#include "Net.hpp"

namespace net::manager {

class Client {

public:
    explicit Client(asio::ip::udp::endpoint endpoint)
        : _endpoint(std::move(endpoint))
    {
    }

    ~Client() = default;

    [[nodiscard]] asio::ip::udp::endpoint getEndpoint() const
    {
        return _endpoint;
    }

private:
    asio::ip::udp::endpoint _endpoint;
};

}

#endif /* CLIENT_HPP_ */
