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
    for (const auto& i : regi.get_components<Component::position>()) {
        std::cout << "x = " << i->_x << " y = " << i->_y << std::endl;
    }
    for (sparse_array<Component::position>::Components_iterator it = regi.get_components<Component::position>().begin(); it != regi.get_components<Component::position>().end(); ++it) {
        std::cout << "x = " << *it->_x << " y = " << it->_y << std::endl;

}
}
