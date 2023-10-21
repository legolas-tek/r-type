/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** main
*/

#include "GameLoop.hpp"
#include "IGame.hpp"
#include <memory>

void runGame(engine::IGame &game)
{
    engine::Registry reg;

    game.registerAllComponents(reg);
    game.initAssets(reg);
    game.initSounds(reg);
    game.initScene(reg);
    game.registerAdditionalSystems(reg);
    game.registerAdditionalClientSystems(reg);

    gameLoop(reg);
}

int main()
{
    std::unique_ptr<engine::IGame> game(createGame());

    try {
        std::unique_ptr<engine::IGame> lobby(game->createLobby());
        if (lobby)
            runGame(*lobby);
    } catch (engine::IGame::StartGameException const &) {
        // run the game:
    }
    runGame(*game);
}
