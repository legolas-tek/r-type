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

#include <memory>

namespace net::manager {

class TcpServerImpl {
public:
    TcpServerImpl(std::size_t port)
        : _acceptor(
            _io_ctx,
            asio::ip::tcp::endpoint(
                asio::ip::tcp::v4(), asio::ip::port_type(port)
            )
        )
    {
        _acceptor.non_blocking(true);
    }

    ~TcpServerImpl()
    {
        _acceptor.close();
    }

    std::unique_ptr<Tcp> acceptNewClient()
    {
        asio::error_code ec;
        std::unique_ptr<Tcp> tcp = std::make_unique<Tcp>(_acceptor, ec);
        if (ec)
            return nullptr;
        return tcp;
    }

private:
    asio::io_context _io_ctx;
    asio::ip::tcp::acceptor _acceptor;
};

TcpServer::TcpServer(std::size_t port)
    : _impl(std::make_unique<TcpServerImpl>(port))
{
}

TcpServer::~TcpServer() = default;

TcpConnection TcpServer::acceptNewClient()
{
    return _impl->acceptNewClient();
}

}
