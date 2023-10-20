/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** Lobby remote client
*/

#include "LobbyServer.hpp"
#include "Serialization/Serializer.hpp"
#include "TcpNetManager.hpp"

#include <algorithm>
#include <memory>

net::LobbyRemoteClient::LobbyRemoteClient(net::manager::TcpConnection &&network)
    : _network(std::move(network))
{
}

void net::LobbyRemoteClient::sendJoinSuccess(
    std::uint8_t playerNumber, std::uint64_t playerHash
)
{
    engine::Serializer serializer;

    serializer.serializeTrivial(std::byte(0x01));
    serializer.serializeTrivial(playerNumber);
    serializer.serializeTrivial(playerHash);
    _network->write(serializer.finalize());
}

void net::LobbyRemoteClient::sendNewPlayer(
    std::uint8_t playerNumber, std::string const &playerName
)
{
    engine::Serializer serializer;

    serializer.serializeTrivial(std::byte(0x02));
    serializer.serializeTrivial(playerNumber);
    serializer.serializePascalString<std::uint8_t>(playerName);
    _network->write(serializer.finalize());
}

void net::LobbyRemoteClient::sendGameStart()
{
    engine::Serializer serializer;

    serializer.serializeTrivial(std::byte(0x08));
    _network->write(serializer.finalize());
}

void net::LobbyRemoteClient::sendError(std::string const &error)
{
    engine::Serializer serializer;

    serializer.serializeTrivial(std::byte(0xFE));
    serializer.serializePascalString<std::uint8_t>(error);
    _network->write(serializer.finalize());
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
