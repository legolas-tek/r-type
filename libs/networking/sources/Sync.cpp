/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network Sync abstract class
*/

#include "Components/Position.hpp"

#include "Serialization/Deserializer.hpp"
#include "Serialization/Serializer.hpp"
#include "Snapshot.hpp"
#include "UdpNetManager.hpp"

#include "Sync.hpp"
#include <functional>
#include <optional>

#ifdef DEBUG_NETWORK
    #include <iostream>
#endif

net::Sync::Sync(
    net::ClientNetManager, engine::Registry &registry, std::string const &addr,
    int port, size_t playerNumber, size_t playerHash
)
    : _registry(registry)
    , _nmu(std::make_unique<net::manager::Udp>(
          net::client_netmanager, addr, port
      ))
    , _rd_index(0)
    , _playerNumber(playerNumber)
    , _playerHash(playerHash)
    , _isServer(false)
{
}

net::Sync::Sync(
    net::ServerNetManager, engine::Registry &registry, std::string const &addr,
    int port, std::vector<net::lobby::RemoteClient> const &lobby
)
    : _registry(registry)
    , _nmu(std::make_unique<net::manager::Udp>(
          net::server_netmanager, addr, port
      ))
    , _rd_index(0)
    , _playerNumber(0)
    , _playerHash(0)
    , _isServer(true)
{
    for (auto &client : lobby) {
        _nmu->getOthers().emplace_back(
            client.getPlayerName(), client.getPlayerNumber(),
            client.getPlayerHash(), std::nullopt
        );
    }
}

net::Sync::~Sync() = default;

bool net::Sync::canUpdate(
    [[maybe_unused]] manager::Client const &client,
    [[maybe_unused]] engine::Entity entity,
    [[maybe_unused]] uint8_t component_id,
    [[maybe_unused]] engine::Deserializer deser
)
{
    return true;
}

bool net::Sync::canSend(
    [[maybe_unused]] engine::Entity entity,
    [[maybe_unused]] uint8_t component_id
)
{
    return true;
}

void net::Sync::sendAckPacket(
    uint32_t tickNumber, net::manager::Client const &client
)
{
    engine::Serializer serializer;

    serializer.serializeTrivial(_playerHash);
    serializer.serializeTrivial(std::byte(0x02));
    serializer.serializeTrivial(tickNumber);
    _nmu->send(serializer.finalize(), client);

#ifdef DEBUG_NETWORK
    std::cout << "SyncSystem: sent ack packet for tick " << tickNumber
              << std::endl;
#endif
}

void net::Sync::applyInterpolationNeededUpdates()
{
    engine::Deserializer deserializer(_lastUpdate);
    std::size_t velocityComponentId
        = _registry.get_component_id<Component::Position>();

    deserializer.skip(
        sizeof(std::size_t) + sizeof(uint8_t) + (sizeof(uint32_t) * 2)
    );

    while (not deserializer.isFinished()) {
        uint32_t entity_nbr = 0;
        deserializer.deserializeTrivial(entity_nbr);

        if (entity_nbr >= 500)
            // invalid entity number
            return;

        engine::Entity entity(entity_nbr);

        uint8_t component_id = 0;
        deserializer.deserializeTrivial(component_id);

        bool updateType = false;
        deserializer.deserializeTrivial(updateType);

        if (updateType) {
            if (component_id != velocityComponentId) {
                _registry.apply_data(
                    engine::Entity(0), component_id, deserializer
                );
                _registry.erase_component(engine::Entity(0), component_id);
                continue;
            }
            _registry.apply_data(entity, component_id, deserializer);
        }
    }
}

void net::Sync::processUpdatePacket(
    engine::Deserializer &deserializer, net::manager::Client &client
)
{
    uint32_t tickNumber;
    deserializer.deserializeTrivial(tickNumber);

    if (tickNumber <= client._lastTick)
        return;

    client._lastTick = tickNumber;
    deserializer.skip(sizeof(uint32_t)); // skip the previous tick number

    while (not deserializer.isFinished()) {
        uint32_t entity_nbr = 0;
        deserializer.deserializeTrivial(entity_nbr);

        if (entity_nbr >= 500)
            // invalid entity number
            return;

        engine::Entity entity(entity_nbr);

        uint8_t component_id = 0;
        deserializer.deserializeTrivial(component_id);

        bool updateType = false;
        deserializer.deserializeTrivial(updateType);

        if (not canUpdate(client, entity, component_id, deserializer)) {
            // update disallowed, use the trash entity
            entity = engine::Entity(0);
        }

        if (updateType) {
            // apply the update
            _registry.apply_data(entity, component_id, deserializer);
        }

        if (not updateType or entity == 0) {
            // erase the component, or the trash entity
            _registry.erase_component(entity, component_id);
        }
    }

    if (not _isServer)
        applyInterpolationNeededUpdates();

#ifdef DEBUG_NETWORK
    std::cout << "SyncSystem: received " << deserializer.getOffset()
              << " byte update packet for tick " << tickNumber << std::endl;
#endif

    sendAckPacket(tickNumber, client);
}

void net::Sync::processAckPacket(
    engine::Deserializer &deserializer, net::manager::Client &client
)
{
    uint32_t tick_number = 0;
    deserializer.deserializeTrivial(tick_number);

#ifdef DEBUG_NETWORK
    std::cout << "SyncSystem: received ack of tick " << tick_number
              << std::endl;
#endif

    auto snapshot_it = std::find_if(
        _snapshots.begin(), _snapshots.end(),
        [&](SnapshotHistory &i) { return i.snapshot.tick == tick_number; }
    );

    if (snapshot_it == _snapshots.end())
        return;

    std::size_t index = (&client) - _nmu->getOthers().data();

    // mark the snapshot as acked by the client number by its index
    snapshot_it->ack_mask |= (std::size_t(1) << index);
}

net::Snapshot &net::Sync::find_last_ack(std::size_t client_index)
{
    for (int i = 0; i != net::SNAPSHOT_NBR; ++i) {
        unsigned int index = (_rd_index - i) % net::SNAPSHOT_NBR;

        auto &snapshot = _snapshots[index];

        if (snapshot.snapshot.wasAck) {
            // use the dummy snapshot, which is always acked
            return snapshot.snapshot;
        }

        if (snapshot.ack_mask & (std::size_t(1) << client_index)) {
            // the snapshot was acked by the client
            return snapshot.snapshot;
        }
    }

    return _dummy;
}

std::vector<std::byte> net::Sync::constructUpdatePacket(
    net::Snapshot const &previous, net::Snapshot const &current,
    net::Snapshot::CanSend canSend
)
{
    engine::Serializer serializer;

    serializer.serializeTrivial(_playerHash);
    serializer.serializeTrivial(std::byte(0x01));
    serializer.serializeTrivial(std::uint32_t(current.tick));
    serializer.serializeTrivial(std::uint32_t(previous.tick));

    size_t size = serializer.getSize();
    net::diffSnapshots(serializer, previous, current, canSend);
    if (serializer.getSize() == size && previous.tick != 0) {
        return {}; // no update
    }
    return serializer.finalize();
}

void net::Sync::updateSnapshotHistory(net::Snapshot &&current)
{
    _rd_index = (_rd_index + 1) % net::SNAPSHOT_NBR;

    SnapshotHistory &snap = _snapshots[_rd_index];
    snap.snapshot = std::move(current);
    snap.ack_mask = 0;
}

void net::Sync::operator()()
{
    auto received = _nmu->receive();

    for (auto &[buffer, endpoint] : received) {
        if (not _isServer && _lastUpdate.empty()) {
            _lastUpdate = std::move(buffer);
            continue;
        }

        try {
            engine::Deserializer deserializer(_isServer ? buffer : _lastUpdate);
            std::size_t playerHash = 0;

            deserializer.deserializeTrivial(playerHash);
            auto *client = getClientWithHash(playerHash);

            if (not client)
                continue;
            client->_endpoint = endpoint;

            std::uint8_t packetId = 0;

            deserializer.deserializeTrivial(packetId);
            switch (packetId) {
            case 0x01:
                processUpdatePacket(deserializer, *client);
                break;
            case 0x02:
                processAckPacket(deserializer, *client);
                break;
            }

            if (not _isServer)
                _lastUpdate = std::move(buffer);
        } catch (engine::Deserializer::DeserializerError &e) {
        }
    }

    if (_isServer and _registry.getTick() % net::SERVER_TIME_STEP == 0)
        return;

    auto &clients = _nmu->getOthers();

    for (auto it = clients.begin(); it != clients.end(); it++) {
        Snapshot &previous = find_last_ack(it - clients.begin());
        Snapshot current(_registry.getTick(), _registry);

        auto packet = constructUpdatePacket(
            previous, current,
            [this](engine::Entity entity, uint8_t component_id) {
                return this->canSend(entity, component_id);
            }
        );

        if (packet.empty())
            continue;

#ifdef DEBUG_NETWORK
        std::cout << "SyncSystem: sent " << packet.size()
                  << " byte update packet for tick " << previous.tick << " -> "
                  << _registry.getTick() << std::endl;
#endif
        updateSnapshotHistory(std::move(current));
        _nmu->send(packet, *it);
    }
}

net::manager::Client *net::Sync::getClientWithHash(std::size_t hash)
{
    for (auto &client : _nmu->getOthers()) {
        if (client._playerHash == hash)
            return &client;
    }
    return nullptr;
}

std::size_t net::Sync::getPlayerNumber(manager::Client const &client) const
{
    return client._playerNumber;
}
