/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** Lobby client
*/

#include "LobbyManager.hpp"
#include "TcpNetManager.hpp"

#include <algorithm>

net::LobbyClient::LobbyClient(std::string addr, std::size_t port)
    : _network(addr, port)
{
}

void net::LobbyClient::sendJoinRequest(std::string const &playerName)
{
    size_t playerNameSize = std::min(playerName.size(), 0xffUL);
    std::vector<std::byte> data(2 + playerNameSize, std::byte(0));

    data[0] = std::byte(0x01);
    data[1] = std::byte(playerNameSize);
    std::memcpy(&data[2], playerName.data(), playerNameSize);

    _network.write(data);
}

void net::LobbyClient::sendStartRequest()
{
    std::vector<std::byte> data(1, std::byte(0x08));

    _network.write(data);
}

void net::LobbyClient::operator()()
{
    CircularBuffer &buffer = _network.getBuffer();
    std::size_t initialIndex;

    try {
        while (buffer.canRead(1)) {
            initialIndex = buffer.getReadIndex();
            parsePacket();
        }
    } catch (CircularBuffer::CannotReadException const &e) {
        // Try again later
        buffer.resetReadIndex(initialIndex);
    }
}

void net::LobbyClient::parsePacket()
{
    CircularBuffer &buffer = _network.getBuffer();
    std::byte id;

    buffer.readInto(&id, sizeof(id));
    switch (id) {
    case std::byte(0x01): {
        // Join success
        uint8_t playerId;
        buffer.readInto(&playerId, sizeof(playerId));
        uint64_t playerHash;
        buffer.readInto(&playerHash, sizeof(playerHash));
        onJoinSuccess(playerId, playerHash);
        break;
    }
    case std::byte(0x02): {
        // New player notification
        uint8_t playerId;
        buffer.readInto(&playerId, sizeof(playerId));
        uint8_t playerNameSize;
        buffer.readInto(&playerNameSize, sizeof(playerNameSize));
        std::string playerName(playerNameSize, '\0');
        buffer.readInto(playerName.data(), playerNameSize);
        onNewPlayer(playerId, std::move(playerName));
        break;
    }
    case std::byte(0x08): {
        // Game starts notification
        onGameStart();
        break;
    }
    case std::byte(0xFE): {
        // Error
        uint8_t errorLength;
        buffer.readInto(&errorLength, sizeof(errorLength));
        std::string error(errorLength, '\0');
        buffer.readInto(error.data(), errorLength);
        onError(std::move(error));
        break;
    }
    }
}
