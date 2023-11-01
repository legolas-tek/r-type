/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** Diff Logger
*/

#ifndef R_TYPE_NETWORKING_DIFFLOGGER_HPP
#define R_TYPE_NETWORKING_DIFFLOGGER_HPP

#include "ISystem.hpp"
#include "Registry.hpp"
#include "Snapshot.hpp"
#include <fstream>

namespace net::system {

class DiffLogger : public ISystem {
public:
    DiffLogger(engine::Registry &registry);
    void operator()() override;

private:
    engine::Registry &_registry;
    Snapshot _lastSnapshot;
    std::ofstream _file;
};

} // namespace net::system

#endif /* !R_TYPE_NETWORKING_DIFFLOGGER_HPP */
