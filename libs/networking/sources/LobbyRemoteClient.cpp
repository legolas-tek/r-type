/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** Lobby remote client
*/

#include "LobbyServer.hpp"
#include "TcpNetManager.hpp"

#include <algorithm>
#include <memory>

net::LobbyRemoteClient::LobbyRemoteClient(
    std::unique_ptr<manager::Tcp> &&network
)
    : _network(std::move(network))
{
}

void net::LobbyRemoteClient::sendJoinSuccess(
    std::uint8_t playerNumber, std::uint64_t playerHash
)
{
    std::vector<std::byte> data(2 + sizeof(playerHash));

    data[0] = std::byte(0x01);
    data[1] = std::byte(playerNumber);
    std::memcpy(&data[2], &playerHash, sizeof(playerHash));
    _network->write(data);
}

void net::LobbyRemoteClient::sendNewPlayer(
    std::uint8_t playerNumber, std::string const &playerName
)
{
    std::vector<std::byte> data(3 + playerName.size());

    data[0] = std::byte(0x02);
    data[1] = std::byte(playerNumber);
    data[2] = std::byte(playerName.size());
    std::memcpy(&data[3], playerName.data(), playerName.size());
    _network->write(data);
}

void net::LobbyRemoteClient::sendGameStart()
{
    std::vector<std::byte> data(1, std::byte(0x08));

    _network->write(data);
}

void net::LobbyRemoteClient::sendError(std::string const &error)
{
    std::vector<std::byte> data(2 + error.size());

    data[0] = std::byte(0xFE);
    data[1] = std::byte(error.size());
    std::memcpy(&data[2], error.data(), error.size());
    _network->write(data);
}

void net::LobbyRemoteClient::operator()()
{
    CircularBuffer &buffer = _network->getBuffer();
    std::size_t initialIndex;

    try {
        while (buffer.canRead(1)) {
            initialIndex = buffer.getReadIndex();
            parsePacket();
        }
    } catch (CircularBuffer::CannotReadException const &) {
        // Try again later
        buffer.resetReadIndex(initialIndex);
    }
}

void net::LobbyRemoteClient::parsePacket()
{
    CircularBuffer &buffer = _network->getBuffer();
    std::byte id;

    buffer.readInto(&id, sizeof(id));
    switch (id) {
    case std::byte(0x01): {
        // Join request
        uint8_t playerNameSize;
        buffer.readInto(&playerNameSize, sizeof(playerNameSize));
        std::string playerName(playerNameSize, '\0');
        buffer.readInto(playerName.data(), playerNameSize);
        onJoinRequest(std::move(playerName));
        break;
    }
    case std::byte(0x08): {
        // Start request
        onStartRequest();
        break;
    }
    }
}
