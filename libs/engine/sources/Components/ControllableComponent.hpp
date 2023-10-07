/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** controllable
*/

#ifndef CONTROLLABLE_HPP_
#define CONTROLLABLE_HPP_

namespace Component {

struct Controllable {
    Controllable(int id)
        : _id(id)
    {
    }

    int _id;
};

}

#endif /* !CONTROLLABLE_HPP_ */
