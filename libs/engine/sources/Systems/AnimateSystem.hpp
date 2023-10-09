<<<<<<< HEAD
=======
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

/// @brief This system animates all entities who has the component animate
//using the renderer
namespace System {

class AnimateSystem {
    public:
        AnimateSystem(SparseArray<Component::Drawable> const &drawables, IRendering const &renderer)
        : _drawables(drawables) _renderer(renderer) {}
        AnimateSystem(System::AnimateSystem const &other) = delete;
        void operator()() {
            // system logic
        }
    private:
        SparseArray<Component::Drawable> const &_drawables;
        IRendering const &_renderer; // could/should be std::unique_ptr<std::vector<IRendering>> ??
};
}

#endif /* !ANIMATESYSTEM_HPP_ */
>>>>>>> 6787844 (feat: add some doxygens on the systems)
