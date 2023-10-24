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
    Client(
        std::string playerName, std::size_t playerNumber,
        std::size_t playerHash, std::optional<asio::ip::udp::endpoint> endpoint
    )
        : _playerName(playerName)
        , _playerNumber(playerNumber)
        , _playerHash(playerHash)
        , _endpoint(endpoint)
    {
    }

    /// The player name
    std::string _playerName;
    /// The player number
    std::size_t _playerNumber;
    /// The player hash, for securily identify the player
    std::size_t _playerHash;
    /// The endpoint of the client, which is the last known address of the
    /// client
    std::optional<asio::ip::udp::endpoint> _endpoint;
    /// The last received tick of the client
    std::size_t _lastTick = 0;
};
}

#endif /* CLIENT_HPP_ */
