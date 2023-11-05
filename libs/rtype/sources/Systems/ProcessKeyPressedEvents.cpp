/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ProcessKeyPressedEvents system
*/

#include "Events/KeyPressed.hpp"

#include "ProcessKeyPressedEvents.hpp"

#include <string>

System::ProcessKeyPressedEvents::ProcessKeyPressedEvents(
    event::EventQueue &events, std::size_t playerNumber,
    std::size_t const &tick, SparseArray<Component::Text> &texts,
    SparseArray<Component::ChatModifiableText> &modifiables
)
    : _events(events)
    , _playerNumber(playerNumber)
    , _tick(tick)
    , _previousTick(0)
    , _texts(texts)
    , _modifiables(modifiables)
{
}

void System::ProcessKeyPressedEvents::operator()()
{
    std::string reaction;

    for (auto &keyPressed : _events.getEvents<event::KeyPressed>()) {
        if (keyPressed.key == 'L') {
            reaction = "Lol well done";
        }
        if (keyPressed.key == 'P') {
            reaction = "Fuck you";
        }
    }

    for (auto it = _texts.begin(); it != _texts.end(); ++it) {
        auto &modifiable = _modifiables[it.get_entity()];
        bool isModifiable = modifiable && modifiable->id == _playerNumber;

        if (not isModifiable)
            continue;

        if ((*it)->_text != reaction and reaction != "")
            (*it)->_text = std::move(reaction);
    }
}
