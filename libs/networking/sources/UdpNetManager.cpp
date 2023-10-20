/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** UdpNetManager
*/

#include "UdpNetManager.hpp"

#include <asio/ip/tcp.hpp>
#include <asio/read_until.hpp>
#include <iostream>
#include <vector>

net::manager::Udp::Udp(
    net::ServerNetManager, std::string addr, std::size_t port
)
    : _socket(
        _io_ctxt,
        asio::ip::udp::endpoint(asio::ip::make_address(addr.c_str(), _ec), port)
    )
{
    if (_ec)
        throw UdpNetManagerError(_ec.message());
    _socket.non_blocking(true);
}

net::manager::Udp::Udp(
    net::ClientNetManager, std::string addr, std::size_t port
)
    : _socket(_io_ctxt)
{
    _socket.open(asio::ip::udp::v4());
    _socket.non_blocking(true);

    _others.emplace_back(
        asio::ip::udp::endpoint(asio::ip::make_address(addr.c_str(), _ec), port)
    );
}

net::manager::Udp::~Udp()
{
    _socket.close();
}

void net::manager::Udp::send(
    net::Buffer const &cmd, net::manager::Client const &client
)
{
    _socket.send_to(asio::buffer(cmd.data(), cmd.size()), client.getEndpoint());
}

std::vector<std::pair<net::Buffer, net::manager::Client>>
net::manager::Udp::receive() noexcept
{
    asio::ip::udp::endpoint client_endpoint;
    std::vector<std::pair<net::Buffer, net::manager::Client>> packets;

    do {
        net::Buffer buff(USHRT_MAX, std::byte(0x00));

        try {
            std::size_t buffSize = 0;
            buffSize
                = _socket.receive_from(asio::buffer(buff), client_endpoint);
            buff.resize(buffSize);
        } catch (std::exception &e) {
            break;
        }

        auto it = find_if(_others.begin(), _others.end(), [&](Client &i) {
            return i.getEndpoint() == client_endpoint;
        });

        if (it != _others.end()) {
            packets.emplace_back(buff, *it);
            continue;
        }

        _others.emplace_back(client_endpoint);
        packets.emplace_back(buff, _others.back());
    } while (1);

    return packets;
}

std::vector<net::manager::Client> &net::manager::Udp::getOthers()
{
    return _others;
}
