/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Rail
*/

#ifndef RAIL_HPP_
#define RAIL_HPP_

#include "Serialization/Serializable.hpp"

namespace Component {
enum RailType { SATIC, DYNAMIC };
struct Rail : engine::Serializable<Rail> {
public:
    Rail(RailType type)
        : type(type)
    {
    }
    Rail() = default;

    RailType type;

private:
};
}

#endif /* !RAIL_HPP_ */
