/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Key
*/

#ifndef KEY_HPP_
#define KEY_HPP_

#include "Components/Velocity.hpp"
#include "Components/Controllable.hpp"
#include "Registry.hpp"
#include "ISystem.hpp"

namespace rendering
{
class Key : public ISystem {
    public:
        Key(engine::Registry &registry);
        ~Key();
        void operator()()
        {
            auto velocity_list = _registry.get_components<Component::Velocity>();

            for (auto it = velocity_list.begin(); it != velocity_list.end(); ++it) {
                // std::cout << it.get_entity() << std::endl;
                auto velocity = _registry.get_components<Component::Velocity>()[it.get_entity()];
                std::cout << "entity " << it.get_entity() << " " << velocity.value()._vx << std::endl;

            }
            std::cout << "asd" << std::endl;
            // std::size_t index = 0;
            // auto drawable_list = _registry.get_components<Component::Drawable>();
            // BeginDrawing();
            // ClearBackground(RAYWHITE);
            // for (auto it = drawable_list.begin(); it != drawable_list.end(); ++it) {
            //     auto pos = _registry.get_components<Component::Position>()[it.get_entity()];

            //     if (_cache.find(it.get_entity()) != _cache.end()) {
            //         DrawTexture(_cache.at(it.get_entity())._texture, pos->_x, pos->_y, WHITE);
            //     } else {
            //         _cache.emplace(it.get_entity(), _registry._assets_paths[(*it)->_index]);
            //         DrawTexture(_cache.at(it.get_entity())._texture, pos->_x, pos->_y, WHITE);
            //     }
            // }
            // EndDrawing();
        }
    protected:
    private:
        engine::Registry &_registry;
};
}
#endif /* !KEY_HPP_ */
