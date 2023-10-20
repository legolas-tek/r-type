/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ISysteme
*/

#include "Snapshot.hpp"
#include <vector>

net::Snapshot::Snapshot()
    : tick(0)
    , wasAck(true)
    , data()
{
}

net::Snapshot::Snapshot(size_t tick, engine::Registry const &registry)
    : tick(tick)
    , wasAck(false)
    , data(registry.collect_data())
{
}

using EntityNumber = uint32_t;
using ComponentId = uint8_t;

static void diffAdd(
    engine::Serializer &diff,
    std::vector<ComponentData>::const_iterator const &it
)
{
    diff.serializeTrivial(EntityNumber(it->entity));
    diff.serializeTrivial(ComponentId(it->componentId));
    diff.serializeTrivial(true);
    diff.insert(it->data);
}

static void diffRemove(
    engine::Serializer &diff,
    std::vector<ComponentData>::const_iterator const &it
)
{
    diff.serializeTrivial(EntityNumber(it->entity));
    diff.serializeTrivial(ComponentId(it->componentId));
    diff.serializeTrivial(false);
}

void net::diffSnapshots(
    engine::Serializer &diff, net::Snapshot const &previous,
    net::Snapshot const &current
)
{
    auto previousIt = previous.data.begin();

    for (auto currentIt = current.data.begin(); currentIt != current.data.end();
         ++currentIt) {
        if (previousIt == previous.data.end()) {
            diffAdd(diff, currentIt);
            continue;
        }
        if (previousIt->componentId == currentIt->componentId
            && previousIt->entity == currentIt->entity) {
            if (previousIt->data != currentIt->data) {
                // modified, send again
                diffAdd(diff, currentIt);
            } // else, unchanged, skip
            ++previousIt;
            continue;
        }
        // different identifiers, either a removal or an addition
        for (auto it = previousIt; it != previous.data.end(); ++it) {
            if (it->componentId == currentIt->componentId
                && it->entity == currentIt->entity) {
                // current exists in previous, so there was a removal
                // for each component in previous that is not in current
                for (auto it2 = previousIt; it2 != it; ++it2) {
                    diffRemove(diff, it2);
                }
                previousIt = it + 1;
                --currentIt; // reprocess current
                break;
            }
        }
        // current does not exist in previous, so it was added
        diffAdd(diff, currentIt);
    }
    // all remaining components in previous are removals
    for (auto it = previousIt; it != previous.data.end(); ++it) {
        diffRemove(diff, it);
    }
}

std::vector<std::byte>
net::diffSnapshots(net::Snapshot const &previous, net::Snapshot const &current)
{
    engine::Serializer diff;
    diffSnapshots(diff, previous, current);
    return diff.finalize();
}
