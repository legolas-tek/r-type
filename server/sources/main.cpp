/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** main
*/

#include "GameLoop.hpp"
#include "IGame.hpp"
#include <memory>

void runGame(std::unique_ptr<engine::IGame> _game)
{
    // make sure the game is destroyed before the registry
    engine::Registry reg;
    std::unique_ptr<engine::IGame> game(std::move(_game));

    game->registerAllComponents(reg);
    game->initAssets(reg);
    game->initScene(reg);
    game->registerAdditionalSystems(reg);
    game->registerAdditionalServerSystems(reg);

    gameLoop(reg);
}

int main()
{
    std::unique_ptr<engine::IGame> game(createGame());

    try {
        std::unique_ptr<engine::IGame> lobby(game->createLobby());
        if (lobby)
            runGame(std::move(lobby));
    } catch (engine::IGame::StartGameException const &) {
        // run the game:
    }
    runGame(std::move(game));
}
