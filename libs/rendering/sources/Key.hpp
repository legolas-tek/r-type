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
#include "raylib.h"

namespace rendering
{
class Key : public ISystem {
    public:
        Key(engine::Registry &registry);
        ~Key();
        void operator()()
        {
            auto &velocity_list = _registry.get_components<Component::Velocity>();
            auto &controlable_list = _registry.get_components<Component::Controllable>();

            for (auto it = velocity_list.begin(); it != velocity_list.end(); ++it) {
                bool isControllable = controlable_list[it.get_entity()].has_value();

                // wasd et zqsd

                // pos 있으면
                if (isControllable) {
                    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_Z)) {
                        velocity_list[it.get_entity()].value()._vx += 0.0f;
                        velocity_list[it.get_entity()].value()._vy += -0.1f;
                    }
                    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_Q)) {
                        velocity_list[it.get_entity()].value()._vx += -0.1f;
                        velocity_list[it.get_entity()].value()._vy += 0.0f;
                    }
                    if (IsKeyDown(KEY_S)) {
                        velocity_list[it.get_entity()].value()._vx += 0.0f;
                        velocity_list[it.get_entity()].value()._vy += 0.1f;
                    }
                    if (IsKeyDown(KEY_D)) {
                        velocity_list[it.get_entity()].value()._vx += 0.1f;
                        velocity_list[it.get_entity()].value()._vy += 0.0f;
                    }
                }
            }
        }
    protected:
    private:
        engine::Registry &_registry;
};
}
#endif /* !KEY_HPP_ */
