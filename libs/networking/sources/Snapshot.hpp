/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ISysteme
*/

#ifndef NETWORKING_SNAPSHOT_HPP_
#define NETWORKING_SNAPSHOT_HPP_

#include <cstddef>
#include <vector>
#include "Entity.hpp"

struct ComponentData {
    /**
     * The id of the entity
     */
    Entity entity;

    /**
     * The id of the component
     */
    size_t componentId;

    /**
     * The data of the component
     */
    std::vector<char> data;
};

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
};

#endif /* !NETWORKING_SNAPSHOT_HPP_ */
