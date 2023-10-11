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
     * Register all needed components into the registry.
     */
    virtual void registerAllComponents(engine::Registry &reg) = 0;

    /**
     * Register extra systems for the client
     */
    virtual void registerAdditionalClientSystems(engine::Registry &reg)
    {
    }

    /**
     * Register extra systems for the server
     */
    virtual void registerAdditionalServerSystems(engine::Registry &reg)
    {
    }

    /**
     * Register extra systems for both client and server
     */
    virtual void registerAdditionalSystems(engine::Registry &reg)
    {
    }

    virtual void initScene(engine::Registry &reg)
    {
    }

    virtual void initAssets(engine::Registry &reg)
    {
    }
};
}

engine::IGame *createGame();

#endif /* !ENGINE_IGAME_H_ */
