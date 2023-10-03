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
    SparseArray<Component> &register_component() {
        SparseArray<Component> array;
        SparseArray<Component> &array_ref = array;

        if (_components_arrays.try_emplace(typeid(SparseArray<Component>), std::move(array)).second)
            _erase_comp_funcs.emplace(typeid(SparseArray<Component>), [](Registry& registry, const Entity& entity) {
                registry.get_components<Component>().erase(entity);
            });
        return array_ref;
    }

    template <class Component>
    SparseArray<Component> &get_components() {
        return std::any_cast<SparseArray<Component> &>(_components_arrays.at(typeid(SparseArray<Component>)));
    }

    template <class Component>
    SparseArray<Component> const &get_components() const {
        return std::any_cast<SparseArray<Component> const &>(_components_arrays.at(typeid(SparseArray<Component>)));
    }

    template <class Component>
    void erase_component(Entity const &entity) {
        _erase_comp_funcs[typeid(SparseArray<Component>)](*this, entity);
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
