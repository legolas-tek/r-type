/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Entity
*/

#ifndef ENTITY_H_
#define ENTITY_H_

#include <cstddef>

class Entity {
    public:
        explicit Entity(size_t value) : _value(value) {}
        operator size_t() const { return _value; }
    private:
        size_t _value;
};

#endif /* !ENTITY_H_ */
