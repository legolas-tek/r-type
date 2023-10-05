/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

namespace Component {
class Drawable {
    Drawable(bool drawable = true)
        : _is_drawable(drawable) {}
    bool _is_drawable;
};
}

#endif /* !DRAWABLE_HPP_ */
