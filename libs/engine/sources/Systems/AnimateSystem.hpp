/*
** EPITECH PROJECT, 2023
** engine
** File description:
** AnimateSystem
*/

#ifndef ANIMATESYSTEM_HPP_
#define ANIMATESYSTEM_HPP_

#include "ISystem.hpp"
#include "SparseArray.hpp"

#include "Components/DrawableComponent.hpp"

namespace System {

template <typename Graphical_objs>
class AnimateSystem {
    public:
        AnimateSystem(SparseArray<Component::Drawable> const &drawables) : _drawables(drawables) {}
        AnimateSystem(System::AnimateSystem const &other) = delete;
        void operator()() {
            // system logic
        }
    private:
        SparseArray<Component::Drawable> const &_drawables;
        Graphical_objs const &_drawable_items; // could/should be std::unique_ptr<std::vector<Graphical_objs>> ??
};
}

#endif /* !ANIMATESYSTEM_HPP_ */
