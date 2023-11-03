/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ISysteme
*/

#include "Snapshot.hpp"
#include "Client.hpp"
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
using UpdateType = bool;

static void diffAdd(
    engine::Serializer &diff, std::size_t clientNumber,
    std::vector<ComponentData>::const_iterator const &it,
    net::Snapshot::CanSend const &canSend
)
{
    if (not canSend(clientNumber, it->entity, it->componentId))
        return;

    diff.serializeTrivial(EntityNumber(it->entity));
    diff.serializeTrivial(ComponentId(it->componentId));
    diff.serializeTrivial(UpdateType(0x01));
    diff.insert(it->data);
}

static void diffRemove(
    engine::Serializer &diff,
    std::vector<ComponentData>::const_iterator const &it
)
{
    diff.serializeTrivial(EntityNumber(it->entity));
    diff.serializeTrivial(ComponentId(it->componentId));
    diff.serializeTrivial(UpdateType(0x00));
}

void net::diffSnapshots(
    std::size_t clientNumber, engine::Serializer &diff,
    net::Snapshot const &previous, net::Snapshot const &current,
    net::Snapshot::CanSend const &canSend
)
{
    auto previousIt = previous.data.begin();

    for (auto currentIt = current.data.begin(); currentIt != current.data.end();
         ++currentIt) {
        if (previousIt == previous.data.end()) {
            diffAdd(diff, clientNumber, currentIt, canSend);
            continue;
        }
        if (previousIt->componentId == currentIt->componentId
            && previousIt->entity == currentIt->entity) {
            if (previousIt->data != currentIt->data) {
                // modified, send again
                diffAdd(diff, clientNumber, currentIt, canSend);
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
                break;
            }
        }
        // current does not exist in previous, so it was added
        diffAdd(diff, clientNumber, currentIt, canSend);
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

    diffSnapshots(
        0, diff, previous, current,
        []([[maybe_unused]] std::size_t clientNumber,
           [[maybe_unused]] engine::Entity entity,
           [[maybe_unused]] uint8_t component_id) { return true; }
    );
    return diff.finalize();
}
