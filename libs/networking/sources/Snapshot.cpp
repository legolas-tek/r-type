/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ISysteme
*/

#include "Snapshot.hpp"
#include "Registry.hpp"
#include <vector>

Snapshot::Snapshot()
    : tick(0)
    , wasAck(true)
    , data()
{
}

Snapshot::Snapshot(size_t tick, Registry const &registry)
    : tick(tick)
    , wasAck(false)
    , data(registry.collect_data())
{
}

std::vector<char>
diffSnapshots(Snapshot const &previous, Snapshot const &current)
{
}
