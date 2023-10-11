/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** main
*/

#include "Registry.hpp"
#include "IGame.hpp"
#include "GameLoop.hpp"

#include "Components/Controllable.hpp"


int main(int argc, char *argv[])
{
    engine::Registry reg;
    engine::IGame &game = *createGame();

    game.registerAllComponents(reg);
    game.initAssets(reg);
    game.initScene(reg);
    game.registerAdditionalSystems(reg);
    game.registerAdditionalClientSystems(reg);

    gameLoop(reg);
}
