/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** R-type
*/

#include "R-Type.hpp"
#include "Entity.hpp"
#include "SparseArray.hpp"
#include "Registry.hpp"
#include "position.hpp"
#include "velocity.hpp"
#include "drawable.hpp"
#include <vector>
#include <algorithm>
#include <memory>
#include <unistd.h>
#include <SFML/Window.hpp>
#include "Sfml_SpriteFactory.hpp"

#define WIDTH 1980
#define HEIGHT 1080

void position_system(Registry &regi);
void draw_system(Registry &regi, sf::RenderWindow window);

class component
{
public:
	component(int a = 0, int b = 0) : _a(a), _b(b) {}
	int _a;
	int _b;
};

class component2
{
public:
	component2(int c = 0, int d = 0) : _c(c), _d(d) {}
	int _c;
	int _d;
};

void logging_system(Registry &r)
{
	auto const &positions = r.get_components<Component::position>();
	auto const &velocities = r.get_components<Component::velocity>();

	for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i)
	{
		auto const &pos = positions[i];
		auto const &vel = velocities[i];
		if (pos && vel)
		{
			std::cerr << i << " : Position = { " << pos.value()._x << " , " << pos.value()._y << " } , Velocity = { " << vel.value()._vx << " , " << vel.value()._vy << " } " << std ::endl;
		}
	}
}

int main()
{
	Registry reg;
	Entity player(0);
	Entity target(4);
	Entity test(2);
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My window");
	Sprite background("ressources/sand.png", sf::Rect<int>(0, 0, WIDTH, HEIGHT));

	reg.register_component<Component::position>();
	reg.register_component<Component::velocity>();
	reg.register_component<Component::drawable>();
	reg.get_components<Component::position>().insert_at(player, std::move(Component::position(1, 200)));
	reg.get_components<Component::position>().insert_at(target, std::move(Component::position(1, 500)));
	reg.get_components<Component::velocity>().insert_at(player, std::move(Component::velocity(5, 0)));
	reg.get_components<Component::velocity>().insert_at(target, std::move(Component::velocity(5, 0)));
	reg.get_components<Component::drawable>().insert_at(player, std::move(Component::drawable(std::move(Sprite("ressources/alex.png", sf::Rect<int>(0, 0, 32, 32))))));
	reg.get_components<Component::drawable>().insert_at(target, std::move(Component::drawable(std::move(Sprite("ressources/alex.png", sf::Rect<int>(0, 0, 32, 32))))));
    // run the program as long as the window is open
    while (window.isOpen())
    {
		window.clear(sf::Color::Black);
		usleep(100000);
		logging_system(reg);
		position_system(reg);
		window.draw(background.getSprite());
    	for (auto it = reg.get_components<Component::drawable>().begin(); it != reg.get_components<Component::drawable>().end(); ++it) {
    	    if ((*it)->_is_drawable)
    	        window.draw((*it)->_sprite.getSprite());
    	}
		window.display();
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}
