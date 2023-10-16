/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** TcpNetManager
*/

#include "TcpNetManager.hpp"
#include "TcpConnection.hpp"
#include "TcpServer.hpp"

#include <asio/ip/tcp.hpp>
#include <asio/read_until.hpp>
#include <iostream>
#include <memory>
#include <vector>

net::manager::Tcp::Tcp(std::string addr, std::size_t port)
    : _buffer(BUFFER_SIZE)
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

net::manager::Tcp::Tcp(asio::ip::tcp::acceptor &acceptor, asio::error_code &ec)
    : _buffer(BUFFER_SIZE)
    , _socket(_io_ctx)
{
    acceptor.accept(_socket, ec);
    reader();
    _t = std::thread([&]() { return _io_ctx.run(); });
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

net::manager::TcpConnection::TcpConnection(std::unique_ptr<Tcp> &&impl)
    : _impl(std::move(impl))
{
}

net::manager::TcpConnection::~TcpConnection() = default;
net::manager::TcpConnection::TcpConnection(net::manager::TcpConnection &&)
    = default;
net::manager::TcpConnection &
net::manager::TcpConnection::operator=(net::manager::TcpConnection &&)
    = default;

net::manager::TcpConnection::operator bool() const
{
    return _impl != nullptr;
}

net::manager::Tcp *net::manager::TcpConnection::operator->()
{
    return _impl.get();
}
