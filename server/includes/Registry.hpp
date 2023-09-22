/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include "SparseArray.hpp"
#include <typeindex>
#include <unordered_map>
#include <any>

class Registry
{
public:

    template <class Component>
    sparse_array<Component> &register_component() {
        sparse_array<Component> array;
        sparse_array<Component> &array_ref = array;

        _components_arrays.try_emplace(typeid(sparse_array<Component>), std::move(array));
        return array_ref;
    }

    template <class Component>
    sparse_array<Component> &get_components() {
        return std::any_cast<sparse_array<Component> &>(_components_arrays.at(typeid(sparse_array<Component>))); //TODO: change it to fit the return type, convert the std::any to a Component
    }

    template <class Component>
    sparse_array<Component> const &get_components() const {
        return std::any_cast<sparse_array<Component> const &>(_components_arrays.at(typeid(sparse_array<Component>))); //TODO: change it to fit the return type, convert the std::any to a Component
    }

private:
    std::unordered_map<std::type_index, std::any> _components_arrays;
};

#endif /* !REGISTRY_HPP_ */
