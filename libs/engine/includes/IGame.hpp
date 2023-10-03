/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game Interface
*/

#ifndef ENGINE_IGAME_H_
#define ENGINE_IGAME_H_

#include "Registry.hpp"

class IGame {
public:
    /**
     * Register all needed components into the registry.
     */
    virtual void registerAllComponents(Registry &reg) = 0;

    /**
     * Register extra systems for the client
     */
    virtual void registerAdditionalClientSystems(Registry &reg)
    {
    }

    /**
     * Register extra systems for the server
     */
    virtual void registerAdditionalServerSystems(Registry &reg)
    {
    }

    /**
     * Register extra systems for both client and server
     */
    virtual void registerAdditionalSystems(Registry &reg)
    {
    }
};

#endif /* !ENGINE_IGAME_H_ */
