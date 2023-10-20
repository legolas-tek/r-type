/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** UdpNetManager
*/

#include "UdpNetManager.hpp"
#include "Net.hpp"
#include "asio/ip/detail/endpoint.hpp"

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
        "server", 0, 0,
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
    if (auto endpoint = client._endpoint) {
        _socket.send_to(asio::buffer(cmd.data(), cmd.size()), *endpoint);
    }
}

std::vector<std::pair<net::Buffer, asio::ip::udp::endpoint>>
net::manager::Udp::receive() noexcept
{
    asio::ip::udp::endpoint client_endpoint;
    std::vector<std::pair<net::Buffer, asio::ip::udp::endpoint>> packets;
    asio::error_code ec;

    do {
        net::Buffer buff(USHRT_MAX, std::byte(0x00));
        std::size_t buffSize
            = _socket.receive_from(asio::buffer(buff), client_endpoint, 0, ec);
        if (ec)
            break;
        buff.resize(buffSize);
        packets.emplace_back(std::move(buff), client_endpoint);
    } while (1);

    return packets;
}

std::vector<net::manager::Client> &net::manager::Udp::getOthers()
{
    return _others;
}
