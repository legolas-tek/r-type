/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ISysteme
*/

#include "Snapshot.hpp"
#include "Registry.hpp"

Snapshot createSnapshot(size_t tick, Registry &registry)
{
    Snapshot snapshot;

    snapshot.tick = tick;
    snapshot.wasAck = false;
    snapshot.data = registry.collect_data();
    return snapshot;
}
