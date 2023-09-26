/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Position_systeme
*/

#ifndef POSITION_SYSTEME_HPP_
#define POSITION_SYSTEME_HPP_

#include "ISysteme.hpp"
#include "position.hpp"
#include "velocity.hpp"
#include "Registry.hpp"

class Position_systeme : public ISysteme<void (Registry &,
					sparse_array<Component::position> const &,
					sparse_array<Component::velocity> const &)> {
    public:
        Position_systeme operator()() {
            _func
        }
};

#endif /* !POSITION_SYSTEME_HPP_ */
