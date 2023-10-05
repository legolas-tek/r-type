/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Power
*/

#ifndef POWER_HPP_
    #define POWER_HPP_

#include <cstddef>

namespace Component {

struct Power {
    Power(int id, int power) : _id(id), _power(power) {}

    int _id;
    int _power;
};

}