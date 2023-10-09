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

namespace net {

constexpr struct ServerNetManager {
} server_netmanager;
constexpr struct ClientNetManager {
} client_netmanager;

using Buffer = std::vector<std::byte>;

namespace manager {

class Udp {

public:
    Udp(net::ServerNetManager, std::string addr, std::size_t port);
    Udp(net::ClientNetManager, std::string addr, std::size_t port);
    ~Udp();

    void send(net::Buffer &cmd);

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

    std::vector<std::pair<net::Buffer, net::manager::Udp::Client>> receive() noexcept;
    std::vector<Udp::Client> &getOthers();

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

    std::vector<Udp::Client> _others;
};

}

}

#endif /* UDPNETMANAGER_HPP_ */
