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

#include "Client.hpp"
#include "Net.hpp"

namespace net {

namespace manager {

class Udp {

public:
    Udp(net::ServerNetManager, std::string addr, std::size_t port);
    Udp(net::ClientNetManager, std::string addr, std::size_t port);
    ~Udp();

    void send(net::Buffer const &cmd, net::manager::Client const &client);
    std::vector<std::pair<net::Buffer, net::manager::Client>>
    receive() noexcept;
    std::vector<Client> &getOthers();

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

    asio::io_context _io_ctxt;

    asio::ip::udp::socket _socket;

    std::vector<Client> _others;

    bool _isClient;
};

}

}

#endif /* UDPNETMANAGER_HPP_ */
