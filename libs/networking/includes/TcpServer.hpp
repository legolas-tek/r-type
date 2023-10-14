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

class TcpServer {
public:
    TcpServer(std::size_t port);

    std::unique_ptr<Tcp> acceptNewClient();

private:
    std::unique_ptr<TcpServerImpl> _impl;
};

}

#endif /* !R_TYPE_NETWORKING_TCP_SERVER_HPP */
