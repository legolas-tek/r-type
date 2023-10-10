/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** main
*/

#include "Registry.hpp"
#include "RTypeGame.cpp"

#include "Components/Controllable.hpp"


int main(int argc, char *argv[])
{
    engine::Registry reg;
    RTypeGame game;

    game.registerAllComponents(reg);
    game.registerInitAssets(reg);
    game.registerInitScene(reg);
    game.registerAdditionalClientSystems(reg);

    while (1) {
        reg.run_systems();
    }
}
