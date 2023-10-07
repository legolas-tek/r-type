/*
** EPITECH PROJECT, 2023
** zappy gui
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

std::size_t net::manager::Udp::send(net::manager::Udp::Buffer &cmd)
{
    std::size_t totalSended = 0;

    for (auto &client : _others) {
        totalSended += _socket.send_to(
            asio::buffer(cmd.data(), cmd.size()), client.getEndpoint()
        );
    }
    return totalSended;
}

std::vector<net::manager::Udp::Buffer> net::manager::Udp::receive() noexcept
{
    asio::ip::udp::endpoint client_endpoint;
    std::vector<net::manager::Udp::Buffer> packets;
    std::size_t totalReaded = 0;

    do {
        Udp::Buffer buff(USHRT_MAX);

        try {
            totalReaded
                = _socket.receive_from(asio::buffer(buff), client_endpoint);
        } catch (std::exception &e) {
            break;
        }
        packets.push_back(buff);

        if (find_if(
                _others.begin(), _others.end(),
                [&](Udp::Client &i) {
                    return i.getEndpoint() == client_endpoint;
                }
            )
                != _others.end())
            continue;

        _others.emplace_back(client_endpoint);
        totalReaded = 0;
    } while (totalReaded == 0);

    return packets;
}

std::vector<net::manager::Udp::Client> &net::manager::Udp::getOthers()
{
    return _others;
}
