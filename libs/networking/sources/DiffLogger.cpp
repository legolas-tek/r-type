/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** Diff Logger
*/

#include "DiffLogger.hpp"
#include "Snapshot.hpp"

#include <iomanip>

#ifdef _WIN32
    #include <process.h>
    #define getpid _getpid
#else
    #include <unistd.h>
#endif

net::system::DiffLogger::DiffLogger(engine::Registry &registry)
    : _registry(registry)
{
    auto pid = getpid();
    _file.open(
        "ticks-" + std::to_string(pid) + ".diff",
        std::ios::out | std::ios::trunc
    );
}

void net::system::DiffLogger::operator()()
{
    Snapshot currentSnapshot(_registry.getTick(), _registry);
    auto buffer = diffSnapshots(_lastSnapshot, currentSnapshot);

    if (buffer.empty())
        return; // No diff

    _lastSnapshot = std::move(currentSnapshot);

    _file << "====" << std::endl;
    _file << "Tick: " << _registry.getTick() << std::endl;
    _file << "Size: " << buffer.size() << std::endl;
    _file << "====" << std::endl;

    engine::Deserializer deserializer(buffer);
    while (not deserializer.isFinished()) {
        // Get component metadata
        uint32_t entity;
        deserializer.deserializeTrivial(entity);
        uint8_t componentId;
        deserializer.deserializeTrivial(componentId);
        bool update;
        deserializer.deserializeTrivial(update);

        if (update) {
            // Get component data size, by putting it in the trash entity
            size_t loc = deserializer.getOffset();
            _registry.apply_data(engine::Entity(0), componentId, deserializer);
            size_t size = deserializer.getOffset() - loc;
            _registry.erase_component(engine::Entity(0), componentId);

            _file << "+ Entity(" << entity << ") Component("
                  << size_t(componentId) << ") Size(" << size << ") Value(";
            for (size_t i = 0; i < size; i++) {
                if (i != 0)
                    _file << " ";
                _file << std::hex << std::setfill('0') << std::setw(2)
                      << std::right << (int) buffer[loc + i];
            }
            _file << std::dec << ")" << std::endl;
        } else {
            _file << "- Entity(" << entity << ") Component("
                  << size_t(componentId) << ")" << std::endl;
        }
    }
}
