/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** systems
*/

#include "Registry.hpp"
#include "position.hpp"
#include "velocity.hpp"

void position_system(Registry &regi)
{
    for (auto it = regi.get_components<Component::position>().begin(); it != regi.get_components<Component::position>().end(); it++) {
        std::cout << "x = " << (*it)->_x << " y = " << (*it)->_y << " iterations = " << it.get_iterations() << std::endl;
        if (regi.get_components<Component::velocity>()[it.get_iterations()].has_value())
            std::cout << "test ver x = " << (*it)->_x << " y = " << (*it)->_y << std::endl;
    }
}
