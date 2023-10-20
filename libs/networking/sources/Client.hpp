/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Client class of the net namespace
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <asio.hpp>
#include <optional>

#include "Net.hpp"

namespace net::manager {

struct Client {
    /// The player name
    std::string _playerName;
    /// The player number
    std::size_t _playerNumber;
    /// The player hash, for securily identify the player
    std::size_t _playerHash;
    /// The endpoint of the client, which is the last known address of the
    /// client
    std::optional<asio::ip::udp::endpoint> _endpoint;
};
}

#endif /* CLIENT_HPP_ */
