/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** TCP Connection
*/

#ifndef R_TYPE_NETWORKING_TCP_CONNECTION_HPP
#define R_TYPE_NETWORKING_TCP_CONNECTION_HPP

#include <cstddef>
#include <memory>

namespace net::manager {

class Tcp;

/**
 * @brief A TCP Connection
 */
class TcpConnection {
public:
    /// Creates a new TCP connection wrapper around the given implementation
    TcpConnection(std::unique_ptr<Tcp> &&impl);
    /// Destroys the TCP connection
    ~TcpConnection();

    TcpConnection(TcpConnection const &) = delete;
    TcpConnection &operator=(TcpConnection const &) = delete;
    TcpConnection(TcpConnection &&) noexcept;
    TcpConnection &operator=(TcpConnection &&) noexcept;

    /// Checks if this object refers to a valid tcp connection
    operator bool() const;

    Tcp *operator->();

private:
    /// The PIMPL to hide implementation details of the tcp connection
    std::unique_ptr<Tcp> _impl;
};

}

#endif /* !R_TYPE_NETWORKING_TCP_CONNECTION_HPP */
