/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Tcp Net Manager
*/

#ifndef TCPNETMANAGER_HPP_
#define TCPNETMANAGER_HPP_

#include <asio.hpp>
#include <exception>
#include <future>
#include <string>
#include <thread>

#include "CircularBuffer.hpp"
#include "TcpServer.hpp"

namespace net::manager {

class Tcp {
    static inline constexpr std::size_t BUFFER_SIZE = 1024 * 6;

public:
    Tcp(std::string addr, std::size_t port);
    Tcp(asio::ip::tcp::acceptor &acceptor, asio::error_code &ec);
    ~Tcp();

    CircularBuffer &getBuffer();

    void write(std::vector<std::byte> const &data);

    class TcpNetManagerError : public std::exception {

    public:
        TcpNetManagerError(std::string const &msg)
            : _msg(msg)
        {
        }

        char const *what() const noexcept override
        {
            return _msg.c_str();
        }

    private:
        std::string _msg;
    };

private:
    void reader();

    asio::error_code _ec;

    net::CircularBuffer _buffer;

    asio::io_context _io_ctx;

    asio::ip::tcp::socket _socket;

    std::thread _t;
};

}

#endif /* TCPNETMANAGER_HPP_ */
