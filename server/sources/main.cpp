/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** main
*/

#include "GameLoop.hpp"
#include "IGame.hpp"
#include "Registry.hpp"

int main(int argc, char *argv[])
{
    engine::Registry reg;
    std::unique_ptr<engine::IGame> game(createGame());

    game->registerAllComponents(reg);
    game->initAssets(reg);
    game->initScene(reg);
    game->registerAdditionalSystems(reg);
    game->registerAdditionalServerSystems(reg);

    gameLoop(reg);
}

