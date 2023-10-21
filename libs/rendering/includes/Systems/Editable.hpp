/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Editable System
*/

#ifndef R_TYPE_EDITABLE_SYSTEM_HPP
#define R_TYPE_EDITABLE_SYSTEM_HPP

#include "Components/Editable.hpp"
#include "Components/Focusable.hpp"
#include "Components/Text.hpp"

#include "ISystem.hpp"
#include "SparseArray.hpp"

namespace rendering::system {

struct Editable : public ISystem {
    explicit Editable(
        SparseArray<Component::Editable> &editables,
        SparseArray<Component::Focusable> &focusables,
        SparseArray<Component::Text> &texts
    );
    ~Editable() override;
    void operator()() override;

private:
    SparseArray<Component::Editable> &_editables;
    SparseArray<Component::Focusable> &_focusables;
    SparseArray<Component::Text> &_texts;
};
}

#endif // R_TYPE_EDITABLE_SYSTEM_HPP
