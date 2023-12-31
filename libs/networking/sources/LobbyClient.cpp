/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** Lobby client
*/

#include "LobbyClient.hpp"
#include "Serialization/Serializer.hpp"
#include "TcpNetManager.hpp"

#include <algorithm>

net::LobbyClient::LobbyClient(std::string const &addr, std::size_t port)
    : _network(std::make_unique<manager::Tcp>(addr, port))
{
}

void net::LobbyClient::sendJoinRequest(std::string const &playerName)
{
    engine::Serializer serializer;

    serializer.serializeTrivial(std::byte(0x01));
    serializer.serializePascalString<std::uint8_t>(playerName);
    _network->write(serializer.finalize());
}

void net::LobbyClient::sendSpectateRequest()
{
    engine::Serializer serializer;

    serializer.serializeTrivial(std::byte(0x03));
    _network->write(serializer.finalize());
}

void net::LobbyClient::sendStartRequest()
{
    engine::Serializer serializer;

    serializer.serializeTrivial(std::byte(0x08));
    _network->write(serializer.finalize());
}

void net::LobbyClient::operator()()
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

void net::LobbyClient::parsePacket()
{
    CircularBuffer &buffer = _network->getBuffer();
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
    case std::byte(0x03): {
        // Spectate success
        uint64_t playerHash;
        buffer.readInto(&playerHash, sizeof(playerHash));
        onSpectateSuccess(playerHash);
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
