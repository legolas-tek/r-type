/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** TCP Server
*/

#ifndef R_TYPE_NETWORKING_TCP_SERVER_HPP
#define R_TYPE_NETWORKING_TCP_SERVER_HPP

#include <cstddef>
#include <memory>

namespace net::manager {

class TcpServerImpl;
class Tcp;

/**
 * @brief A TCP Server, which can accept connections from new clients
 */
class TcpServer {
public:
    /// Creates a new TCP Server, listening on the gven port
    TcpServer(std::size_t port);

    /// Accepts a new client if there is one, and returns a tcp connection to
    /// it, or nullptr if there is no pending connections
    std::unique_ptr<Tcp> acceptNewClient();

private:
    /// The PIMPL to hide implementation details of the tcp server
    std::unique_ptr<TcpServerImpl> _impl;
};

}

#endif /* !R_TYPE_NETWORKING_TCP_SERVER_HPP */
