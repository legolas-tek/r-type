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
#include <vector>
#include <algorithm>

void position_system(Registry &regi);

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

	reg.register_component<Component::position>();
	reg.register_component<Component::velocity>();
	reg.get_components<Component::position>().insert_at(player, std::move(Component::position(1, 2)));
	reg.get_components<Component::position>().insert_at(target, std::move(Component::position(3, 4)));
	reg.get_components<Component::velocity>().insert_at(player, std::move(Component::velocity(5, 6)));
	logging_system(reg);
	position_system(reg);
	return 0;
}

// int main()
// {
	// component comp1(4, 5);
	// component2 comp4(0, 1);
	// Registry regi;
	// Entity first(0);
	// Entity second(1);

	// regi.register_component<component>();
	// regi.register_component<component2>();
	// regi.get_components<component>().insert_at(0, std::move(comp1));
	// regi.get_components<component2>().insert_at(1, std::move(comp4));
	// regi.erase_component<component>(first);
	// std::cout << "component 1:" << std::endl;
	// for (auto comp : regi.get_components<component>())
	// {
	// 	if (comp)
	// 		std::cout << "value _a = " << comp->_a << " value _b = " << comp->_b << std::endl;
	// 	else
	// 		std::cout << "value empty" << std::endl;
	// }
	// std::cout << "component 2:" << std::endl;
	// for (auto comp : regi.get_components<component2>())
	// {
	// 	if (comp)
	// 		std::cout << "value _c = " << comp->_c << " value _d = " << comp->_d << std::endl;
	// 	else
	// 		std::cout << "value empty" << std::endl;
	// }
// }
