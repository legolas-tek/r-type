/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** UdpNetManager
*/

#ifndef UDPNETMANAGER_HPP_
#define UDPNETMANAGER_HPP_

#include <asio.hpp>
#include <exception>
#include <future>
#include <string>

#include <climits>

namespace rtype {

class UdpNetManager {

public:
    using Buffer = std::vector<std::byte>;

public:
    UdpNetManager(std::string addr, std::size_t port);
    ~UdpNetManager();

    std::size_t send(UdpNetManager::Buffer &cmd);

    std::size_t receive();

    Buffer &getPacket();

    class UdpNetManagerError : public std::exception {

    public:
        UdpNetManagerError(std::string const &msg)
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

    asio::error_code _ec;

    Buffer _buffer;

    asio::io_context _io_ctxt;

    asio::ip::udp::endpoint _endpoint;

    asio::ip::udp::socket _socket;

};

}

#endif /* UDPNETMANAGER_HPP_ */
