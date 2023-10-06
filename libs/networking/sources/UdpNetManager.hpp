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

constexpr struct ServerNetmanager{} server_netmanager;
constexpr struct ClientNetmanager{} client_netmanager;

namespace manager {

class Udp {

public:
    using Buffer = std::vector<std::byte>;

public:
    Udp(net::ServerNetmanager, std::string addr, std::size_t port);
    Udp(net::ClientNetmanager, std::string addr, std::size_t port);
    ~Udp();

    std::size_t send(Udp::Buffer &cmd);

    std::vector<Udp::Buffer> receive();

    class Client {

    public:
        Client(asio::ip::udp::endpoint const &endpoint)
            : _endpoint(endpoint) {}

        ~Client() = default;

        asio::ip::udp::endpoint &getEndpoint()
        {
            return _endpoint;
        }

    private:
        asio::ip::udp::endpoint _endpoint;
    };

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