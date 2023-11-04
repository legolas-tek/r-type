/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Jump
*/

#ifndef JUMP_HPP_
#define JUMP_HPP_

#include "Serialization/Serializable.hpp"

namespace Component {

struct Jump : engine::Serializable<Jump> {
public:
    Jump() = default;

private:
    bool isJumping = false;
};
}
#endif /* !JUMP_HPP_ */
