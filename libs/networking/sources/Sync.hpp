/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network Sync abstract class
*/

#ifndef SYNC_HPP_
#define SYNC_HPP_

#include "ISystem.hpp"
#include "Registry.hpp"

#include "UdpNetManager.hpp"
#include "Snapshot.hpp"

namespace net {

class Sync : public ISystem {

public:
    using process_packet_t = void (std::pair<net::Buffer, net::manager::Udp::Client> const &);

public:
    Sync(net::ClientNetManager, engine::Registry &registry, int port);
    Sync(net::ServerNetManager, engine::Registry &registry, int port);
    ~Sync();

    void operator()();
    void processUpdatePacket(std::pair<net::Buffer, net::manager::Udp::Client> const &packet);

private:

    virtual bool canUpdate(engine::Entity &entity, uint8_t component_id, std::byte const *buffer);

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

    std::optional<std::vector<net::Sync::SnapshotHistory>::iterator> find_last_ack(std::size_t client_index);

    std::vector<SnapshotHistory> _snapshots;
    std::size_t _rd_index;

};

}

#endif /* SYNC_HPP_ */
