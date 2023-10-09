/*
** EPITECH PROJECT, 2023
** engine
** File description:
** DrawSystem
*/

#ifndef DRAWSYSTEM_HPP_
#define DRAWSYSTEM_HPP_

#include "ISystem.hpp"
#include "SparseArray.hpp"

#include "Components/PositionComponent.hpp"
#include "Components/DrawableComponent.hpp"

/// @brief This system draws in the window every entity that has the drawable
//components using the renderer
namespace System {

template <typename Graphical_objs>
class DrawSystem : public ISystem {
    public:
        DrawSystem(
            SparseArray<Component::Position> const &positions,
            SparseArray<Component::Drawable> const &_drawables
            std::unique_ptr<Graphical_objs> drawable_items,
        ) : _positions(positions), _drawables(_drawables), _drawable_items(_drawable_items) {}
        DrawSystem(System::DrawSystem const &other) = delete;
        void operator()() {
            // system logic
        }
    private:
        SparseArray<Component::Position> const &_positions;
        SparseArray<Component::Drawable> const &_drawables;
        Graphical_objs const &_drawable_items; // could/should be std::unique_ptr<std::vector<Graphical_objs>> ??
};
}

#endif /* !DRAWSYSTEM_HPP_ */
