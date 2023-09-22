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
#include <vector>
#include <algorithm>

class component {
public:
	component(int a = 0, int b = 0) : _a(a), _b(b) {}
	int _a;
	int _b;
};

class component2 {
public:
	component2(int c = 0, int d = 0) : _c(c), _d(d) {}
	int _c;
	int _d;
};

int main()
{
	Entity first(2);
	size_t test = first;
	component comp1(4, 5);
	component comp2(2, 3);
	component comp3(6, 8);
	Registry regi;

	regi.register_component<component>();
	regi.register_component<component2>();
	regi.get_components<component>().insert_at(0, std::move(comp1));
	regi.get_components<component>().insert_at(5, std::move(comp2));
	regi.get_components<component>().insert_at(1, std::move(comp3));
	// std::cout << "Hello CMake. " << (*array.begin())->_a << " " << (*(array.end() - 1))->_a << std::endl;
	for (auto comp: regi.get_components<component>()) {
		if (comp)
			std::cout << "value _a = " << comp->_a << " value _b = " << comp->_b << std::endl;
		else
			std::cout << "value empty" << std::endl;
	}
	for (auto comp: regi.get_components<component2>()) {
		if (comp)
			std::cout << "value _c = " << comp->_c << " value _d = " << comp->_d << std::endl;
		else
			std::cout << "value empty" << std::endl;
	}
	return 0;
}
