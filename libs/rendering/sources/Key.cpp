/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Key
*/

#include "Key.hpp"
#include "SparseArray.hpp"
#include "raylib.h"

rendering::system::Key::Key(
    SparseArray<Component::Controllable> &controllables,
    SparseArray<Component::Velocity> &velocities, std::uint8_t playerNumber
)
    : _controllables(controllables)
    , _velocities(velocities)
    , _playerNumber(playerNumber)
{
}

rendering::system::Key::~Key()
{
}

void rendering::system::Key::operator()()
{
    for (auto it = _velocities.begin(); it != _velocities.end(); ++it) {
        auto &controllable = _controllables[it.get_entity()];
        auto &velocity = **it;
        bool isControllable
            = controllable && controllable->_id == _playerNumber;

        if (isControllable) {
            velocity._vx = 0.0f;
            velocity._vy = 0.0f;
            if (IsKeyDown(KEY_W) || IsKeyDown(KEY_Z)) {
                velocity._vx += 0.0f;
                velocity._vy += -5.0f;
            }
            if (IsKeyDown(KEY_A) || IsKeyDown(KEY_Q)) {
                velocity._vx += -5.0f;
                velocity._vy += 0.0f;
            }
            if (IsKeyDown(KEY_S)) {
                velocity._vx += 0.0f;
                velocity._vy += 5.0f;
            }
            if (IsKeyDown(KEY_D)) {
                velocity._vx += 5.0f;
                velocity._vy += 0.0f;
            }
        }
    }
}
