/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TcpTcpNetManager
*/

#ifndef TCPNETMANAGER_HPP_
    #define TCPNETMANAGER_HPP_

    #include <string>
    #include <exception>
    #include <thread>
    #include <future>
    #include <asio.hpp>

    #include "CircularBuffer.hpp"

    #define BUFF_SIZE 1024 * 6

namespace rtype {

class TcpNetManager
{

public:
    TcpNetManager(std::string addr, std::size_t port);
    ~TcpNetManager();

    bool canRead();

    std::string getLastResponse();

    void write(std::string cmd);

    class TcpNetManagerError : public std::exception {

    public:
        TcpNetManagerError(const std::string &msg) : _msg(msg) {}

        const char *what() const noexcept override
        {
            return _msg.c_str();
        }

    private:
        std::string _msg;
    };

private:

    void reader();

    asio::error_code _ec;

    rtype::CircularBuffer _buffer;

    asio::io_context _io_ctxt;

    asio::ip::tcp::endpoint _endpoint;

    asio::ip::tcp::socket _socket;

    std::thread _t;
};

}

#endif /* TCPNETMANAGER_HPP_ */
