/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** MarioGame
*/

#ifndef MARIOGAME_HPP_
#define MARIOGAME_HPP_

#include "IGame.hpp"

class MarioGame : public engine::IGame {
public:
    // MarioGame();
    // ~MarioGame();

    void registerAllComponents(engine::Registry &reg) override;

    void registerAdditionalServerSystems(engine::Registry &reg) override;
    void registerAdditionalClientSystems(engine::Registry &reg) override;
    void registerAdditionalSystems(engine::Registry &reg) override;

    void initAssets(engine::Registry &reg) override;
    void initScene(engine::Registry &reg) override;

protected:
private:
};

#endif /* !MARIOGAME_HPP_ */
