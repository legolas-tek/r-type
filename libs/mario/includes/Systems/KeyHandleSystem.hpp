/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** KeyHandleSystem
*/

#ifndef KEY_HANDLE_SYSTEM_HPP_
#define KEY_HANDLE_SYSTEM_HPP_

#include "ISystem.hpp"

#include "Events/EventQueue.hpp"

#include "Registry.hpp"

namespace System {
class KeyHandleSystem : public ISystem {
public:
    KeyHandleSystem(engine::Registry &reg, Event::EventQueue &events);

    void operator()() override;

private:
    engine::Registry &_reg;
    Event::EventQueue &_events;
};
}
#endif /* !KEY_HANDLE_SYSTEM_HPP_ */
