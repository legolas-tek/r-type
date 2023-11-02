/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ISysteme
*/

#ifndef NETWORKING_SNAPSHOT_HPP_
#define NETWORKING_SNAPSHOT_HPP_

#include "Entity.hpp"
#include "Registry.hpp"
#include "Serialization/Serializer.hpp"

#include <cstddef>
#include <vector>

namespace net {

struct Snapshot {

    using can_send_t
        = std::function<bool(engine::Entity entity, uint8_t component_id)>;

    /**
     * The tick the snapshot was taken
     */
    size_t tick;

    /**
     * If the snapshot was acknowledged
     */
    bool wasAck;

    /**
     * The data of the snapshot
     */
    std::vector<ComponentData> data;

    /** The dummy snapshot */
    Snapshot();
    /** Snapshot the current state of a registry */
    Snapshot(size_t tick, engine::Registry const &registry);

    // Delete copy as they are expensive
    Snapshot &operator=(Snapshot const &other) = delete;
    Snapshot(Snapshot const &other) = delete;

    // But allow move
    Snapshot &operator=(Snapshot &&other) = default;
    Snapshot(Snapshot &&other) = default;
};

std::vector<std::byte>
diffSnapshots(Snapshot const &previous, Snapshot const &current);

void diffSnapshots(
    engine::Serializer &diff, Snapshot const &previous, Snapshot const &current,
    net::Snapshot::can_send_t canSend
);
}

#endif /* !NETWORKING_SNAPSHOT_HPP_ */
