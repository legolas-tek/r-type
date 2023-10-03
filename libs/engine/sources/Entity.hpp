/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity
*/

#ifndef ENTITY_H_
#define ENTITY_H_

#include <cstddef>

class Entity {

public:
    explicit Entity(std::size_t value);
    operator std::size_t() const
    {
        return _value;
    }

private:
    std::size_t _value;
};

#endif /* !ENTITY_H_ */
