/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ISysteme
*/

#include "Snapshot.hpp"
#include "Registry.hpp"
#include <cstring>
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

static void diffAdd(
    std::vector<std::byte> &diff,
    std::vector<ComponentData>::const_iterator const &it
)
{
    size_t offset = diff.size();
    diff.resize(
        offset + sizeof(uint64_t) + sizeof(uint8_t) + sizeof(bool)
        + it->data.size()
    );
    std::memcpy(&diff[offset], &it->entity, sizeof(uint64_t));
    offset += sizeof(uint64_t);
    std::memcpy(&diff[offset], &it->componentId, sizeof(uint8_t));
    offset += sizeof(uint8_t);
    diff.push_back(std::byte(0x01));
    offset += sizeof(bool);
    std::memcpy(&diff[offset], it->data.data(), it->data.size());
}

static void diffRemove(
    std::vector<std::byte> &diff,
    std::vector<ComponentData>::const_iterator const &it
)
{
    size_t offset = diff.size();
    diff.resize(
        offset + sizeof(uint64_t) + sizeof(uint8_t) + sizeof(bool)
    );
    std::memcpy(&diff[offset], &it->entity, sizeof(uint64_t));
    offset += sizeof(uint64_t);
    std::memcpy(&diff[offset], &it->componentId, sizeof(uint8_t));
    offset += sizeof(uint8_t);
    diff.push_back(std::byte(0x00));
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
    return diff;
}
