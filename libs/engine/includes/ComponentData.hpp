/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Component data
*/

#ifndef ENGINE_COMPONENTDATA_HPP_
#define ENGINE_COMPONENTDATA_HPP_

#include "Entity.hpp"

#include <vector>

struct ComponentData {
    /**
     * The id of the entity
     */
    Entity entity;

    /**
     * The id of the component
     */
    size_t componentId;

    /**
     * The serialized data of the component
     */
    std::vector<char> data;
};

#endif /* !ENGINE_COMPONENTDATA_HPP_ */
