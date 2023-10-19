/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** main
*/

#include "GameLoop.hpp"
#include "IGame.hpp"
#include "Registry.hpp"
#include <memory>

void runGame(engine::IGame &game)
{
    engine::Registry reg;

    game.registerAllComponents(reg);
    game.initAssets(reg);
    game.initScene(reg);
    game.registerAdditionalSystems(reg);
    game.registerAdditionalServerSystems(reg);

    gameLoop(reg);
}

int main(int argc, char *argv[])
{
    std::unique_ptr<engine::IGame> game(createGame());

    // try {
    // std::unique_ptr<engine::IGame> lobby(game->createLobby());
    // if (lobby)
    // runGame(*lobby);
    //} catch (engine::IGame::StartGameException const &e) {
    //// run the game:
    //}
    std::cout << "Starting game" << std::endl;
    runGame(*game);
}
