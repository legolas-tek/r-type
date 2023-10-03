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
#include <list>

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

    template <typename System, class... Params>
    void add_system(Params &&...args) {
        _systems.emplace_back(std::make_unique<System>(std::forward<Params>(args)...));
    }

    void run_systems() {
        for (auto &system : _systems)
            (*system)();
    }

private:
    std::unordered_map<std::type_index, std::any> _components_arrays;
    std::unordered_map<std::type_index, std::function<void (Registry &, Entity const &)>> _erase_comp_funcs;
    std::vector<std::unique_ptr<ISystem>> _systems;
};

#endif /* !REGISTRY_HPP_ */