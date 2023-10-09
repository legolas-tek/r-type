/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ISysteme
*/

#include "Snapshot.hpp"
#include <cstring>
#include <vector>

Snapshot::Snapshot()
    : tick(0)
    , wasAck(true)
    , data()
{
}

Snapshot::Snapshot(size_t tick, engine::Registry const &registry)
    : tick(tick)
    , wasAck(false)
    , data(registry.collect_data())
{
}

using EntityNumber = uint32_t;
using ComponentId = uint8_t;
using UpdateType = bool;

static void diffAdd(
    std::vector<std::byte> &diff,
    std::vector<ComponentData>::const_iterator const &it
)
{
    size_t offset = diff.size();
    diff.resize(
        offset + sizeof(EntityNumber) + sizeof(ComponentId) + sizeof(UpdateType)
        + it->data.size()
    );
    std::memcpy(&diff[offset], &it->entity, sizeof(EntityNumber));
    offset += sizeof(EntityNumber);
    std::memcpy(&diff[offset], &it->componentId, sizeof(ComponentId));
    offset += sizeof(ComponentId);
    diff[offset] = std::byte(0x01);
    offset += sizeof(UpdateType);
    std::memcpy(&diff[offset], it->data.data(), it->data.size());
}

static void diffRemove(
    std::vector<std::byte> &diff,
    std::vector<ComponentData>::const_iterator const &it
)
{
    size_t offset = diff.size();
    diff.resize(
        offset + sizeof(EntityNumber) + sizeof(ComponentId) + sizeof(UpdateType)
    );
    std::memcpy(&diff[offset], &it->entity, sizeof(EntityNumber));
    offset += sizeof(EntityNumber);
    std::memcpy(&diff[offset], &it->componentId, sizeof(ComponentId));
    offset += sizeof(ComponentId);
    diff[offset] = std::byte(0x00);
}

std::vector<std::byte>
diffSnapshots(Snapshot const &previous, Snapshot const &current)
{
    std::vector<std::byte> diff;
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
    return diff;
}
