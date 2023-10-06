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
    UdpNetManager(std::string addr);
    ~UdpNetManager();

    std::size_t send(UdpNetManager::Buffer &cmd);

    std::vector<rtype::UdpNetManager::Buffer> receive();

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

    std::vector<UdpNetManager::Client> &getOthers();

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

    std::vector<UdpNetManager::Client> _others;
};

}

#endif /* UDPNETMANAGER_HPP_ */
