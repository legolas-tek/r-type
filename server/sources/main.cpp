/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** main
*/

#include "Registry.hpp"
#include "RTypeGame.cpp"
#include "GameLoop.hpp"

int main(int argc, char *argv[])
{
    engine::Registry reg;
    RTypeGame game;

    game.registerAllComponents(reg);
    game.initAssets(reg);
    game.initScene(reg);
    game.registerAdditionalSystems(reg);
    game.registerAdditionalServerSystems(reg);

    gameLoop(reg);
}

