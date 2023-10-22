/*
** EPITECH PROJECT, 2023
** engine
** File description:
** Start Game Button
*/

#include "Systems/StartGameButton.hpp"
#include "Components/Focusable.hpp"
#include "SparseArray.hpp"
#include "Systems/LobbyClientImpl.hpp"

#include <iostream>

System::StartGameButton::StartGameButton(
    LobbyClientImpl &client, Component::Focusable &focusable
)
    : _client(client)
    , _focusable(focusable)
{
}

void System::StartGameButton::operator()()
{
    if (not _focusable.isFocused)
        return;

    _focusable.isFocused = false;

    std::cout << "Requesting game start" << std::endl;
    _client.sendStartRequest();
}
