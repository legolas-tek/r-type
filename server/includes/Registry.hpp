/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include "SparseArray.hpp"
#include "ISystem.hpp"
#include "Entity.hpp"
#include <typeindex>
#include <unordered_map>
#include <any>
#include <functional>
#include <memory>

class Registry
{
public:

    template <class Component>
    sparse_array<Component> &register_component() {
        sparse_array<Component> array;
        sparse_array<Component> &array_ref = array;

        if (_components_arrays.try_emplace(typeid(sparse_array<Component>), std::move(array)).second)
            _erase_comp_funcs.emplace(typeid(sparse_array<Component>), [](Registry& registry, const Entity& entity) {
                registry.get_components<Component>().erase(entity);
            });
        return array_ref;
    }

    template <class Component>
    sparse_array<Component> &get_components() {
        return std::any_cast<sparse_array<Component> &>(_components_arrays.at(typeid(sparse_array<Component>)));
    }

    template <class Component>
    sparse_array<Component> const &get_components() const {
        return std::any_cast<sparse_array<Component> const &>(_components_arrays.at(typeid(sparse_array<Component>)));
    }

    template <class Component>
    void erase_component(Entity const &entity) {
        _erase_comp_funcs[typeid(sparse_array<Component>)](*this, entity);
    }

    template <class... Components, typename Function>
    void add_system(Function &&f) {
        _systems.emplace(std::function<Function(Components)>(f)...);
    }

    // void run_systems() {
    //     for (auto it = _systems.begin(); it != _systems.end(); it++)
    //         (*it).get()->operator();
    // }

private:
    std::unordered_map<std::type_index, std::any> _components_arrays;
    std::unordered_map<std::type_index, std::function<void (Registry &, Entity const &)>> _erase_comp_funcs;
    std::vector<std::unique_ptr<ISystem>> _systems;
};

#endif /* !REGISTRY_HPP_ */
