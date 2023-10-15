/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** TCP Server
*/

#ifndef R_TYPE_NETWORKING_TCP_SERVER_HPP
#define R_TYPE_NETWORKING_TCP_SERVER_HPP

#include "TcpConnection.hpp"
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
    /// Creates a new TCP Server, listening on the given port
    TcpServer(std::size_t port);
    /// Destroys the TCP server
    ~TcpServer();

    /// Accepts a new client if there is one, and returns a tcp connection to
    /// it, or nullptr if there is no pending connections
    TcpConnection acceptNewClient();

private:
    /// The PIMPL to hide implementation details of the tcp server
    std::unique_ptr<TcpServerImpl> _impl;
};

}

#endif /* !R_TYPE_NETWORKING_TCP_SERVER_HPP */
