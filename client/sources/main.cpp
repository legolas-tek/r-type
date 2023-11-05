/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** main
*/

#include "GameLoop.hpp"
#include "IGame.hpp"
#include <memory>

std::unique_ptr<engine::IGame> runGame(std::unique_ptr<engine::IGame> _game)
{
    // make sure the game is destroyed before the registry
    engine::Registry reg;
    std::unique_ptr<engine::IGame> game(std::move(_game));

    game->registerAllComponents(reg);
    game->initAssets(reg);
    if (game->isClientScene())
        game->initScene(reg);
    game->registerAdditionalSystems(reg);
    game->registerAdditionalClientSystems(reg);

    try {
        gameLoop(reg);
    } catch (engine::IGame::StartGameException const &) {
        return game->createNextGame();
    }
}

int main()
{
    std::unique_ptr<engine::IGame> game(createGame());

    while (game) {
        try {
            game = runGame(std::move(game));
        } catch (GameEndException &) {
            game = std::unique_ptr<engine::IGame>(createGame());
        } catch (GameRestartException &e) {
            game = std::unique_ptr<engine::IGame>(createGame());
        }
    }
}
