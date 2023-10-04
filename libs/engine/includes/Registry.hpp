/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include "Entity.hpp"
#include "ISystem.hpp"
#include "ComponentData.hpp"
#include "SparseArray.hpp"
#include <any>
#include <list>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace engine
{
class Registry {
public:
    template <class Component> SparseArray<Component> &register_component()
    {
        SparseArray<Component> array;
        size_t component_id = _component_arrays.size();
        auto emplace_result = _component_ids.try_emplace(
            typeid(SparseArray<Component>), component_id
        );
        if (!emplace_result.second)
            return get_components<Component>(); // Already registered
        _component_arrays.emplace_back(std::move(array));
        _erase_component_funcs.emplace_back([](Registry &registry,
                                               Entity const &entity) {
            registry.get_components<Component>().erase(entity);
        });
        _serialize_component_funcs.emplace_back([](Registry const &registry) {
            std::vector<ComponentData> data;
            SparseArray<Component> const &array
                = registry.get_components<Component>();
            for (size_t i = 0; i < array.size(); i++) {
                if (!array[i])
                    continue;
                Entity entity(i);
                data.push_back(ComponentData {
                    entity, registry.get_component_id<Component>(),
                    array[i]->serialize() });
            }
            return data;
        });
        _deserialize_component_funcs.emplace_back(
            [](Registry &registry, Entity entity, std::byte const *buffer) {
                SparseArray<Component> &array
                    = registry.get_components<Component>();
                if (!array[entity])
                    array[entity] = Component();
                return array[entity]->deserialize(buffer);
            }
        );
        return std::any_cast<SparseArray<Component> &>(
            _component_arrays[component_id]
        );
    }

    template <class Component> size_t get_component_id() const
    {
        return _component_ids.at(typeid(SparseArray<Component>));
    }

    template <class Component> SparseArray<Component> &get_components()
    {
        return std::any_cast<SparseArray<Component> &>(
            _component_arrays[get_component_id<Component>()]
        );
    }

    template <class Component>
    SparseArray<Component> const &get_components() const
    {
        return std::any_cast<SparseArray<Component> const &>(
            _component_arrays[get_component_id<Component>()]
        );
    }

    template <class Component> void erase_component(engine::Entity const &entity)
    {
        _erase_component_funcs[get_component_id<Component>()](*this, entity);
    }

    void erase_component(Entity const &entity, size_t component_id)
    {
        _erase_component_funcs[component_id](*this, entity);
    }

    template <typename System, class... Params>
    void add_system(Params &&...args)
    {
        _systems.emplace_back(std::make_unique<System>(std::forward<Params>(args
        )...));
    }

    std::vector<ComponentData> collect_data() const
    {
        std::vector<ComponentData> data;

        for (auto &serialize_func : _serialize_component_funcs) {
            auto component_data = serialize_func(*this);
            data.insert(
                data.end(), component_data.begin(), component_data.end()
            );
        }
        return data;
    }

    void apply_data(Entity entity, size_t componentId, std::byte const *buffer)
    {
        _deserialize_component_funcs[componentId](*this, entity, buffer);
    }

    void run_systems()
    {
        for (auto &system : _systems)
            (*system)();
    }

private:
    std::unordered_map<std::type_index, std::any> _components_arrays;
    std::unordered_map<
        std::type_index, std::function<void(Registry &, engine::Entity const &)>>
        _erase_comp_funcs;
    std::vector<std::unique_ptr<ISystem>> _systems;
};
} // namespace engine


#endif /* !REGISTRY_HPP_ */
