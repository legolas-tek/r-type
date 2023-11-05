/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Gravity
*/

#ifndef GRAVITY_HPP_
#define GRAVITY_HPP_

#include "Serialization/Serializable.hpp"

namespace Component {
struct Gravity : engine::Serializable<Gravity> {
public:
    Gravity() = default;
    bool isOffset = false;
};
}
#endif /* !GRAVITY_HPP_ */
