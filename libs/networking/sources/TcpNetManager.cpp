/*
** EPITECH PROJECT, 2023
** zappy gui
** File description:
** TcpNetManager
*/

#include "TcpNetManager.hpp"

#include <asio/ip/tcp.hpp>
#include <asio/read_until.hpp>
#include <iostream>
#include <vector>

net::manager::Tcp::Tcp(std::string addr, std::size_t port)
    : _buffer(BUFF_SIZE)
    , _endpoint(asio::ip::make_address(addr.c_str(), _ec), port)
    , _socket(_io_ctxt)
{
    if (_ec)
        throw TcpNetManagerError(_ec.message());

    _socket.async_connect(_endpoint, [this](std::error_code ec) {
        if (!ec) {
            std::cout << "TcpNetManager: connected." << std::endl;
            reader();
        } else {
            std::cout << "TcpNetManager: failed to connect." << std::endl;
            exit(84);
        }
    });
    _t = std::thread([&]() { return _io_ctxt.run(); });
}

net::manager::Tcp::~Tcp()
{
    asio::post(_io_ctxt, [this]() { _socket.close(); });

    _t.join();
}

bool net::manager::Tcp::canRead()
{
    return _buffer.isAvailableData('\n');
}

std::string net::manager::Tcp::getLastResponse()
{
    std::vector<char> res = _buffer.readUntil('\n');

    return std::string(res.begin(), res.end());
}

void net::manager::Tcp::write(std::vector<std::byte> const &data)
{
    _socket.async_write_some(
        asio::buffer(data),
        [this](std::error_code ec, std::size_t writed [[maybe_unused]]) {
            if (ec)
                throw TcpNetManagerError(ec.message());
        }
    );
}

void net::manager::Tcp::reader()
{
    _socket.async_read_some(
        asio::buffer(
            _buffer.getWritePtr(),
            _buffer.getAvailableCapacityUntilWrappingAround()
        ),
        [this](std::error_code ec, std::size_t length) {
            if (!ec) {
                _buffer.updateWriteIndexAfterWrite(length);
                reader();

            } else
                _socket.close();
        }
    );
}
