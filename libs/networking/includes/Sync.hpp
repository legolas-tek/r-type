/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network Sync abstract class
*/

#ifndef SYNC_HPP_
#define SYNC_HPP_

#include <array>
#include <memory>

#include "ISystem.hpp"
#include "Registry.hpp"

#include "Net.hpp"
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
        = void(std::pair<net::Buffer, net::manager::Client> const &);

public:
    /**
     * @brief Construct a new Sync object for the client
     *
     * @param registry the engine registry containing the game state
     * @param port the server port to connect to
     */
    Sync(net::ClientNetManager, engine::Registry &registry, int port);
    /**
     * @brief Construct a new Sync object for the server
     *
     * @param registry the engine registry containing the game state
     * @param port the port use to expose the server
     */
    Sync(net::ServerNetManager, engine::Registry &registry, int port);
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
    virtual bool canUpdate(
        engine::Entity &entity, uint8_t component_id, std::byte const *buffer
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
     * @brief Update the current snapshot history with the newly
     * created snapshot.
     *
     * @param current the current snapshot to store
     */
    void updateSnapshotHistory(net::Snapshot &current);

    engine::Registry &_registry; /// the engine registry
    std::unique_ptr<net::manager::Udp> _nmu; /// the udp net manager

    /**
     * @brief The snapshot history structure represanting
     * a Snapshot and a list of ack users
     */
    struct SnapshotHistory {
        bool used = false; /// is the SnapshotHistory used

        net::Snapshot snapshot; /// the Snapshot
        std::vector<std::size_t>
            ack_users; /// a list of users who acked this Snapshot
    };

    /**
     * @brief We will find the last update packet that this
     * client acked
     *
     * @param client_index the client index
     * @return std::optional<std::array<net::Sync::SnapshotHistory,
     * 32>::iterator> maybe an iterator representing the SnapshotHistoru
     */
    std::optional<
        std::array<net::Sync::SnapshotHistory, NET_SNAPSHOT_NBR>::iterator>
    find_last_ack(std::size_t client_index);

    /**
     * @brief A vector of Snapshots
     */
    std::array<SnapshotHistory, NET_SNAPSHOT_NBR> _snapshots;
    /**
     * @brief The actual index to read the _snapshots
     */
    std::size_t _rd_index;
};

}

#endif /* SYNC_HPP_ */
