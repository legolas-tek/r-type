/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** R-type
*/

#include "R-Type.hpp"
#include "Entity.hpp"
#include "SparseArray.hpp"
#include <vector>
#include <algorithm>

class component {
public:
	component(int a = 0, int b = 0) : _a(a), _b(b) {}
	int _a;
	int _b;
};

int main()
{
	Entity first(2);
	size_t test = first;
	sparse_array<component> array;
	component comp1(4, 5);
	component comp2(2, 3);
	component comp3(6, 8);

	array.insert_at(0, std::move(comp1));
	array.insert_at(5, std::move(comp2));
	array.insert_at(1, std::move(comp3));
	// std::cout << "Hello CMake. " << (*array.begin())->_a << " " << (*(array.end() - 1))->_a << std::endl;
	std::for_each(array.begin(), array.end(), [](std::optional<component> comp) {
		if (comp)
			std::cout << "value _a = " << comp->_a << " value _b = " << comp->_b << std::endl;
		else
			std::cout << "value empty" << std::endl;
	});
	return 0;
}
