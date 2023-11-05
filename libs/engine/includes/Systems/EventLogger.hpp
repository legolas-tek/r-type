/*
** EPITECH PROJECT, 2023
** R-Type Engine
** File description:
** Event Logger
*/

#ifndef R_TYPE_ENGINE_EVENTLOGGER_HPP_
#define R_TYPE_ENGINE_EVENTLOGGER_HPP_

#include "Events/EventQueue.hpp"
#include "ISystem.hpp"

#include <fstream>

namespace System {

class EventLogger : public ISystem {
public:
    EventLogger(
        std::string const &name, std::size_t const &tick,
        event::EventQueue &queue
    );
    void operator()() override;

private:
    std::size_t const &_tick;
    event::EventQueue &_queue;
    std::ofstream _file;
};

}

#endif /* !R_TYPE_ENGINE_EVENTLOGGER_HPP_ */
