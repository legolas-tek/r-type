/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network Sync abstract class
*/

#ifndef SYNC_HPP_
#define SYNC_HPP_

#include <array>
#include <functional>
#include <memory>

#include "ISystem.hpp"
#include "Lobby.hpp"
#include "Registry.hpp"

#include "Net.hpp"
#include "Serialization/Deserializer.hpp"
#include "Snapshot.hpp"

namespace net {

inline constexpr std::size_t NET_SNAPSHOT_NBR = 32;

/**
 * @brief Sync system abstract class.
 * This abstract contain the needed function for a network sync system to work
 * It will be inherited by the server and client classes in order to create a
 * system made for the client and the server.
 */
class Sync : public ISystem {

public:
    /**
     * @brief Using for the functions that process received packets.
     */
    using process_packet_t
        = void(engine::Deserializer &, net::manager::Client const &);

public:
    /**
     * @brief Construct a new Sync object for the client
     *
     * @param registry the engine registry containing the game state
     * @param port the server port to connect to
     */
    Sync(
        net::ClientNetManager, engine::Registry &registry, int port,
        size_t playerNumber, std::size_t playerHash
    );
    /**
     * @brief Construct a new Sync object for the server
     *
     * @param registry the engine registry containing the game state
     * @param port the port use to expose the server
     */
    Sync(
        net::ServerNetManager, engine::Registry &registry, int port,
        std::vector<net::lobby::RemoteClient> const &lobby
    );
    /**
     * @brief Destroy the Sync object
     */
    ~Sync();

    /**
     * @brief Overload of the () operator, that will be used to call all
     * the engine systems
     */
    void operator()();

private:
    /**
     * @brief The snapshot history structure represanting
     * a Snapshot and a list of ack users
     */
    struct SnapshotHistory {
        net::Snapshot snapshot; ///< the snapshot
        std::size_t ack_mask; ///< a bit mask of the users who acked it
    };

private:
    virtual bool canUpdate(
        engine::Entity entity, uint8_t component_id, engine::Deserializer deser
    );

    /**
     * @brief Function to process the received update packet
     *
     * @param packet the received packet to process
     */
    process_packet_t processUpdatePacket;
    /**
     * @brief Function to process the received ack packet
     */
    process_packet_t processAckPacket;

    /**
     * @brief Function to send an ack packet
     */
    void sendAckPacket(uint32_t tickNumber, net::manager::Client const &client);

    /**
     * @brief Update the current snapshot history with the newly
     * created snapshot.
     *
     * @param current the current snapshot to store
     */
    void updateSnapshotHistory(net::Snapshot &&current);

    /**
     * @brief Find the last acked snapshot
     *
     * @param client_index the client index who acked the snapshot
     * @return net::Snapshot& the find snapshot, or dummy if no one find
     */
    net::Snapshot &find_last_ack(std::size_t client_index);

    /**
     * @brief Get a Client object, from its hash
     *
     * @param hash the hash of the client
     * @return net::manager::Client* a pointer to the client, or nullptr if none
     */
    manager::Client *getClientWithHash(std::size_t hash);

protected:
    engine::Registry &_registry; ///< the engine registry

private:
    std::unique_ptr<net::manager::Udp> _nmu; ///< the udp net manager

    std::array<SnapshotHistory, NET_SNAPSHOT_NBR>
        _snapshots; ///< A vector of Snapshots

    std::size_t _rd_index; ///< The actual index to read the _snapshots

    net::Snapshot _dummy; ///< The dummy packet to use in special case

    std::size_t _playerNumber; ///< Our player number, or 0 if server
    std::size_t _playerHash; ///< Our player hash, or 0 if server
};

}

#endif /* SYNC_HPP_ */
