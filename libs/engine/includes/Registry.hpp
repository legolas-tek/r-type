/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include "ComponentData.hpp"
#include "Entity.hpp"
#include "Events/EventQueue.hpp"
#include "Events/IEvent.hpp"
#include "ISystem.hpp"
#include "Serialization/Deserializer.hpp"
#include "Serialization/Serializer.hpp"
#include "SparseArray.hpp"
#include <any>
#include <functional>
#include <list>
#include <memory>
#include <optional>
#include <queue>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace engine {
struct TextureWrapper {
    std::string path2d;
    std::optional<std::string> path3d;

    // Constructor
    TextureWrapper(
        std::string const path2d,
        std::optional<std::string> const path3d = std::nullopt
    )
        : path2d(path2d)
        , path3d(path3d)
    {
    }
};
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
                Serializer ser;
                Entity entity(i);
                array[i]->serialize(ser);
                data.push_back(ComponentData {
                    entity, registry.get_component_id<Component>(),
                    ser.finalize() });
            }
            return data;
        });
        _deserialize_component_funcs.emplace_back(
            [](Registry &registry, Entity entity, Deserializer &deser) {
                SparseArray<Component> &array
                    = registry.get_components<Component>();
                if (!array[entity])
                    array[entity] = Component();
                array[entity]->deserialize(deser);
            }
        );
        return std::any_cast<SparseArray<Component> &>(
            _component_arrays[component_id]
        );
    }

    template <class Component> [[nodiscard]] size_t get_component_id() const
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

    template <class Component> void erase_component(Entity entity)
    {
        erase_component(entity, get_component_id<Component>());
    }

    void erase_component(Entity entity, size_t component_id)
    {
        _erase_component_funcs[component_id](*this, entity);
    }

    void erase_entity(Entity entity)
    {
        for (auto it : _component_ids) {
            erase_component(entity, it.second);
        }
        _freedEntities.push(entity);
    }

    /// Remove all entities from the scene
    void reset_scene()
    {
        for (size_t i = 0; i < _entity_counter; i++) {
            erase_entity(Entity(i));
        }
        _entity_counter = 1;
        while (not _freedEntities.empty()) {
            _freedEntities.pop();
        }
    }

    template <typename System, class... Params>
    ISystem &add_system(Params &&...args)
    {
        return *_systemsToAdd.emplace_back(
            std::make_unique<System>(std::forward<Params>(args)...)
        );
    }

    void updateSystems()
    {
        for (auto &system : _systemsToAdd)
            _systems.emplace_back(std::move(system));
        _systemsToAdd.clear();
    }

    [[nodiscard]] std::vector<ComponentData> collect_data() const
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

    void apply_data(Entity entity, size_t componentId, Deserializer &buffer)
    {
        _deserialize_component_funcs[componentId](*this, entity, buffer);
    }

    void run_systems()
    {
        for (auto &system : _systems)
            (*system)();
    }

    size_t get_new_entity()
    {
        if (not _freedEntities.empty()) {
            engine::Entity newEntity = _freedEntities.front();

            _freedEntities.pop();
            return newEntity;
        }
        return _entity_counter++;
    }

    void incrementTick()
    {
        _tick += 1;
    }

    [[nodiscard]] std::size_t getTick() const
    {
        return _tick;
    }

    [[nodiscard]] std::size_t const &tick() const
    {
        return _tick;
    }

    std::vector<TextureWrapper> _assets_paths;

    event::EventQueue events;

private:
    /// @brief This queue is here to reuse entities that we have deleted before
    std::queue<Entity> _freedEntities;
    /**
     * Map of component type to component id
     */
    std::unordered_map<std::type_index, size_t> _component_ids;
    /**
     * 'Map' of component id to component array
     */
    std::vector<std::any> _component_arrays;
    /**
     * 'Map' of component id to erase function
     */
    std::vector<std::function<void(Registry &, Entity const &)>>
        _erase_component_funcs;
    /**
     * 'Map' of component id to serialization function
     */
    std::vector<std::function<std::vector<ComponentData>(Registry const &)>>
        _serialize_component_funcs;
    /**
     * 'Map' of component id to deserialization function
     */
    std::vector<std::function<void(Registry &, Entity, Deserializer &)>>
        _deserialize_component_funcs;
    /**
     * List of systems
     */
    std::vector<std::unique_ptr<ISystem>> _systems;
    std::vector<std::unique_ptr<ISystem>> _systemsToAdd;

    size_t _entity_counter = 1;

    std::size_t _tick = 1;
};
} // namespace engine

#endif /* !REGISTRY_HPP_ */
