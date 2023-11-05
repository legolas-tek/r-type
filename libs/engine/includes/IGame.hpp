/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game Interface
*/

#ifndef ENGINE_IGAME_H_
#define ENGINE_IGAME_H_

#include "Registry.hpp"

namespace engine {

class IGame {
public:
    virtual ~IGame() = default;

    /**
     * Register all of the game's components into the registry.
     */
    virtual void registerAllComponents(engine::Registry &reg) = 0;

    /**
     * Register extra systems only needed for the client
     */
    virtual void registerAdditionalClientSystems(engine::Registry &)
    {
    }

    /**
     * Register extra systems only needed for the server
     */
    virtual void registerAdditionalServerSystems(engine::Registry &)
    {
    }

    /**
     * Register systems needed for both the client and the server
     */
    virtual void registerAdditionalSystems(engine::Registry &)
    {
    }

    /**
     * Initialize the initial entities of the game
     */
    virtual void initScene(engine::Registry &)
    {
    }

    /**
     * Initialize the assets of the game, into the `Registry::_assets_paths`
     * vector
     */
    virtual void initAssets(engine::Registry &)
    {
    }

    /**
     * Create the next game. It will be run when this game throws a
     * StartGameException.
     */
    virtual std::unique_ptr<engine::IGame> createNextGame()
    {
        return nullptr;
    }

    /**
     * @brief Check if the game draws the scene client side
     *
     * @return true if the scene is created client-side, false by default
     */
    virtual bool isClientScene() const
    {
        return false;
    }

    /**
     * @brief The exception thrown when the game should start after the lobby
     *
     * This exception is thrown when the game should start, and is caught by
     * the main, which then starts the real game. The lobby game must override
     * the `createNextGame` method to return a non-null pointer to a game.
     */
    class StartGameException : public std::exception {
    public:
        [[nodiscard]] char const *what() const noexcept override
        {
            return "Next game requested";
        }
    };
};
}

engine::IGame *createGame();

#endif /* !ENGINE_IGAME_H_ */
