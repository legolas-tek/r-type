/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameLoop
*/

#ifndef GAMELOOP_HPP_
#define GAMELOOP_HPP_

#include "Registry.hpp"

class GameEndException : public std::exception {
public:
    [[nodiscard]] char const *what() const noexcept override
    {
        return "End of game";
    }
};

[[noreturn]] void gameLoop(engine::Registry &reg);

#endif /* !GAMELOOP_HPP_ */
