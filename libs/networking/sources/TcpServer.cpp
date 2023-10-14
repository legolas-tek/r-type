/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** TCP server
*/

#include "TcpServer.hpp"
#include "TcpNetManager.hpp"
#include "asio/error_code.hpp"
#include "asio/io_context.hpp"
#include "asio/ip/tcp.hpp"

#include <asio.hpp>

#include <cstddef>
#include <memory>

namespace net::manager {

class TcpServerImpl {
public:
    TcpServerImpl(std::size_t port)
        : _acceptor(_io_ctx, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
    {
        _acceptor.non_blocking(true);
    }

    std::unique_ptr<Tcp> acceptNewClient()
    {
        asio::ip::tcp::socket socket(_io_ctx);
        _acceptor.accept(socket);
        return std::unique_ptr<Tcp>(new Tcp(_io_ctx, std::move(socket)));
    }

private:
    asio::io_context _io_ctx;
    asio::ip::tcp::acceptor _acceptor;
};

TcpServer::TcpServer(std::size_t port)
    : _impl(new TcpServerImpl(port))
{
}

std::unique_ptr<Tcp> TcpServer::acceptNewClient()
{
    return _impl->acceptNewClient();
}

}
