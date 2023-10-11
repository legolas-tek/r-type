/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ISysteme
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

class ISystem {
public:
    virtual ~ISystem() = default;
    virtual void operator()() = 0;
};

#endif /* !ISYSTEM_HPP_ */
