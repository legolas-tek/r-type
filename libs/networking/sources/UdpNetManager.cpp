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

rtype::UdpNetManager::UdpNetManager(std::string addr, std::size_t port)
    : _buffer(USHRT_MAX)
    , _endpoint(asio::ip::make_address(addr.c_str(), _ec), port)
    , _socket(_io_ctxt)
{
    if (_ec)
        throw UdpNetManagerError(_ec.message());

    _socket.non_blocking(true);
}

rtype::UdpNetManager::~UdpNetManager()
{
    _socket.close();
}

std::size_t rtype::UdpNetManager::send(rtype::UdpNetManager::Buffer &cmd)
{
    return _socket.send_to(asio::buffer(cmd.data(), cmd.size()), _endpoint);
}

std::size_t rtype::UdpNetManager::receive()
{
    return _socket.receive_from(asio::buffer(_buffer), _endpoint);
}

rtype::UdpNetManager::Buffer &rtype::UdpNetManager::getPacket()
{
    return _buffer;
}
