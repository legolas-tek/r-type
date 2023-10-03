/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** systems
*/

#include "Registry.hpp"
#include "position.hpp"
#include "velocity.hpp"
#include <memory>

void position_system(Registry &regi)
{
    for (auto it = regi.get_components<Component::position>().begin();
         it != regi.get_components<Component::position>().end(); ++it) {
        if (auto velocity
            = regi.get_components<Component::velocity>()[it.get_entity()]) {
            (*it)->_x += velocity->_vx;
            (*it)->_y += velocity->_vy;
        }
        // if
        // (regi.get_components<Component::drawable>()[it.get_entity()].has_value())
        // regi.get_components<Component::drawable>()[it.get_entity()]->_sprite.getSprite().setPosition((*it)->_x,
        // (*it)->_y);
    }
}

// void draw_system(Registry &regi, std::unique_ptr<sf::RenderWindow> window)
//{
// for (auto it = regi.get_components<Component::drawable>().begin(); it !=
// regi.get_components<Component::drawable>().end(); ++it) { if
// ((*it)->_is_drawable) window->draw((*it)->_sprite.getSprite());
//}
//}
