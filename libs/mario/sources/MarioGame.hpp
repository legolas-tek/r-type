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

    // a basic size of a unit in pixel
    static inline constexpr float ONE_UNIT = 16.0f;
    static inline constexpr float WIDNOW_SPRITE_WIDTH = 1564.0f;
    static inline constexpr float WIDNOW_SPRITE_HEIGHT = 224.0f;
    static inline constexpr float FLOOR_SPRITE_HEIGHT = 24.0f;
    static inline constexpr float BACKGROUND_SPRITE_HEIGHT = 200.0f;
    static inline constexpr float MARIO_ONE_SPRITE_WIDTH = 150.0f;
    static inline constexpr float MARIO_ONE_SPRITE_HEIGHT = 160.0f;

    void registerAllComponents(engine::Registry &reg) override;

    void registerAdditionalServerSystems(engine::Registry &reg) override;
    void registerAdditionalClientSystems(engine::Registry &reg) override;
    void registerAdditionalSystems(engine::Registry &reg) override;

    void initAssets(engine::Registry &reg) override;
    void initScene(engine::Registry &reg) override;

    bool isClientScene() const override
    {
        return true;
    }

protected:
private:
};

#endif /* !MARIOGAME_HPP_ */
