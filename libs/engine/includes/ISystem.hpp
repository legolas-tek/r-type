/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ISystem
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

#include <cstddef>

class ISystem {
public:
    ISystem(size_t refreshRate = 1)
        : _refreshRate(refreshRate)
    {
    }

    virtual ~ISystem() = default;
    virtual void operator()() = 0;

    size_t _refreshRate;
};

#endif /* !ISYSTEM_HPP_ */
