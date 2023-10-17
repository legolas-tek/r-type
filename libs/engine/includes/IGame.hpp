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
    /**
     * Register all of the game's components into the registry.
     */
    virtual void registerAllComponents(engine::Registry &reg) = 0;

    /**
     * Register extra systems only needed for the client
     */
    virtual void registerAdditionalClientSystems(engine::Registry &reg)
    {
    }

    /**
     * Register extra systems only needed for the server
     */
    virtual void registerAdditionalServerSystems(engine::Registry &reg)
    {
    }

    /**
     * Register systems needed for both the client and the server
     */
    virtual void registerAdditionalSystems(engine::Registry &reg)
    {
    }

    /**
     * Initialize the initial entities of the game
     */
    virtual void initScene(engine::Registry &reg)
    {
    }

    /**
     * Initialize the assets of the game, into the `Registry::_assets_paths`
     * vector
     */
    virtual void initAssets(engine::Registry &reg)
    {
    }

    /**
     * Create the lobby game. It will be run before this game starts, if not
     * null.
     */
    virtual std::unique_ptr<engine::IGame> createLobby()
    {
        return nullptr;
    }

    /**
     * @brief The exception thrown when the game should start after the lobby
     *
     * This exception is thrown when the game should start, and is caught by
     * the main, which then starts the real game.
     */
    class StartGameException : public std::exception {
    public:
        char const *what() const noexcept override
        {
            return "Game is starting, lobby has finished.";
        }
    };
};
}

engine::IGame *createGame();

#endif /* !ENGINE_IGAME_H_ */
