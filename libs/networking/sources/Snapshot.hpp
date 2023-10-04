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
#include <cstddef>
#include <vector>

struct Snapshot {
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
    Snapshot(size_t tick, Registry const &registry);
};

std::vector<char>
diffSnapshots(Snapshot const &previous, Snapshot const &current);

#endif /* !NETWORKING_SNAPSHOT_HPP_ */
