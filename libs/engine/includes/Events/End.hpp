/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** End Game Event
*/

#ifndef R_TYPE_END_GAME_EVENT_HPP
#define R_TYPE_END_GAME_EVENT_HPP

#include "IEvent.hpp"

namespace event {

class EndGame : public IEvent {
public:
    EndGame(bool win)
        : win(win) {};

    void dump(std::ostream &) const override;

    bool win;
};
}

#endif // R_TYPE_END_GAME_EVENT_HPP
