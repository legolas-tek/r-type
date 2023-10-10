/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network sync system
*/

#ifndef NETWORKSYNC_HPP_
#define NETWORKSYNC_HPP_

#include <unordered_map>

#include "ISystem.hpp"
#include "Registry.hpp"

#include "UdpNetManager.hpp"
#include "Snapshot.hpp"

namespace net::system {

class NetworkServerSync : public ISystem {

public:
    using process_packet_t = void (std::pair<net::Buffer, net::manager::Udp::Client> const &);

public:
    NetworkServerSync(engine::Registry &registry, int port);
    ~NetworkServerSync();

    void operator()();

private:
    process_packet_t processReceivedPacket;
    process_packet_t processAckPacket;

    void updateSnapshotHistory(net::Snapshot &current);

    engine::Registry &_registry;
    net::manager::Udp _nmu;

    struct SnapshotHistory {
        bool used = false;

        net::Snapshot snapshot;
        std::vector<std::size_t> ack_users;
    };

    std::optional<std::vector<net::system::NetworkServerSync::SnapshotHistory>::iterator> find_last_ack(std::size_t client_index);

    std::vector<SnapshotHistory> _snapshots;
    std::size_t _rd_index;
};

}

#endif /* NETWORKSYNC_HPP_ */
