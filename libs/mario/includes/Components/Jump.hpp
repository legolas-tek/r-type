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

    bool isJumping = false;
    size_t startJumpTick = 0;
    size_t jumpForTick = 0;

private:
};
}
#endif /* !JUMP_HPP_ */
