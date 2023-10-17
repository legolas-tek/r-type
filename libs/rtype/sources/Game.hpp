/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game
*/

#ifndef R_TYPE_GAME_HPP
#define R_TYPE_GAME_HPP

#include "IGame.hpp"

class RTypeGame : public engine::IGame {
public:
    void registerAllComponents(engine::Registry &reg) override;

    void registerAdditionalServerSystems(engine::Registry &reg) override;
    void registerAdditionalClientSystems(engine::Registry &reg) override;
    void registerAdditionalSystems(engine::Registry &reg) override;

    void initAssets(engine::Registry &reg) override;
    void initScene(engine::Registry &reg) override;
};

#endif /*! R_TYPE_GAME_HPP */
