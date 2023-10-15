/*
** EPITECH PROJECT, 2023
** R-Type Networking
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
    , _io_ctx(_io_ctx_storage)
    , _socket(_io_ctx)
{
    asio::ip::tcp::endpoint endpoint(
        asio::ip::make_address(addr.c_str(), _ec), port
    );
    if (_ec)
        throw TcpNetManagerError(_ec.message());

    _socket.async_connect(endpoint, [this](std::error_code ec) {
        if (!ec) {
            std::cout << "TcpNetManager: connected." << std::endl;
            reader();
        } else {
            std::cout << "TcpNetManager: failed to connect." << std::endl;
            exit(84);
        }
    });
    _t = std::thread([&]() { return _io_ctx.run(); });
}

net::manager::Tcp::Tcp(
    asio::io_context &context, asio::ip::tcp::socket &&socket
)
    : _buffer(BUFF_SIZE)
    , _io_ctx(context)
    , _socket(std::move(socket))
{
    // thread unused, io ctx storage too
}

net::manager::Tcp::~Tcp()
{
    asio::post(_io_ctx, [this]() { _socket.close(); });

    if (_t.joinable())
        _t.join();
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

net::CircularBuffer &net::manager::Tcp::getBuffer()
{
    return _buffer;
}
