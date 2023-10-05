/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** WeaponsComponent
*/

#ifndef WEAPONSCOMPONENT_HPP_
    #define WEAPONSCOMPONENT_HPP_

namespace Component {

struct WeaponsComponent {
    WeaponsComponent(int id, int weaponId) : _id(id), _weaponId(weaponId) {}

    int _id;
    int _weaponId;
};

}

#endif /* !WEAPONSCOMPONENT_HPP_ */