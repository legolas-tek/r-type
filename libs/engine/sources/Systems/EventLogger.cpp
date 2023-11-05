/*
** EPITECH PROJECT, 2023
** R-Type Engine
** File description:
** Event Logger
*/

#include "Systems/EventLogger.hpp"
#include "Events/EventQueue.hpp"

#ifdef _WIN32
    #include <process.h>
    #define getpid _getpid
#else
    #include <unistd.h>
#endif

System::EventLogger::EventLogger(
    std::size_t const &tick, event::EventQueue &queue
)
    : _tick(tick)
    , _queue(queue)
{
    auto pid = getpid();
    _file.open(
        "events-" + std::to_string(pid) + ".log",
        std::ios::out | std::ios::trunc
    );
}

void System::EventLogger::operator()()
{
    if (_queue.begin() == _queue.end())
        return; // empty

    _file << "====" << std::endl;
    _file << "Tick: " << _tick << std::endl;
    _file << "====" << std::endl;
    for (auto &event : _queue) {
        _file << "+ " << typeid(*event).name() << std::endl;
    }
}
