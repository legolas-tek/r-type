/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** R-type
*/

#include "R-Type.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Entity.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"
#include "Systems/LoggingSystem.hpp"
#include <algorithm>
#include <memory>
#include <vector>

#define WIDTH 1980
#define HEIGHT 1080

void position_system(engine::Registry &regi);

void logging_system(
    engine::Registry &reg, SparseArray<Component::Position> const &positions,
    SparseArray<Component::Velocity> const &velocities
)
{
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        auto const &pos = positions[i];
        auto const &vel = velocities[i];
        if (pos && vel) {
            // std ::cerr << i << " : Position = { " << pos.value()._x << " , "
            //            << pos.value()._y << " } , Velocity = { "
            //            << vel.value()._vx << " , " << vel.value()._vy << " } "
            //            << std ::endl;
        }
    }
}

// int main()
//{
// Registry reg;
// Entity background(0);
// Entity player(1);
// Entity target(2);
//  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My window");

// reg.register_component<Component::position>();
// reg.register_component<Component::velocity>();
// reg.register_component<Component::drawable>();
// reg.get_components<Component::position>().insert_at(player,
// std::move(Component::position(1, 200)));
// reg.get_components<Component::position>().insert_at(target,
// std::move(Component::position(1, 500)));
// reg.get_components<Component::velocity>().insert_at(player,
// std::move(Component::velocity(5, 0)));
// reg.get_components<Component::velocity>().insert_at(target,
// std::move(Component::velocity(10, 0)));
//  reg.get_components<Component::drawable>().emplace_at(background,
//  std::move(Sprite("ressources/sand.png", sf::Rect<int>(0, 0, WIDTH,
//  HEIGHT)))); reg.get_components<Component::drawable>().emplace_at(player,
//  std::move(Sprite("ressources/alex.png", sf::Rect<int>(0, 0, 32, 32))));
//  reg.get_components<Component::drawable>().emplace_at(target,
//  std::move(Sprite("ressources/alex.png", sf::Rect<int>(0, 0, 32, 32))));
// reg.add_system<System::Logging>(reg.get_components<Component::position>(),
// reg.get_components<Component::velocity>());
//  run the program as long as the window is open
// reg.run_systems();
// reg.run_systems();
// reg.run_systems();
//  while (window.isOpen())
//  {
//  	window.clear(sf::Color::Black);
//  	usleep(100000);
//  	// logging_system(reg, reg.get_components<Component::position>(),
//  reg.get_components<Component::velocity>());
//  	// position_system(reg);
//  	// reg.run_systems();
//  	window.display();
//  	// check all the window's events that were triggered since the last
//  iteration of the loop 	sf::Event event; 	while
//  (window.pollEvent(event))
//  	{
//  		// "close requested" event: we close the window
//  		if (event.type == sf::Event::Closed)
//  			window.close();
//  	}
//  }

// return 0;
//}
