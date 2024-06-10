/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Seg
*/

#include "Handler/Command/CommandProtocol/Seg.hpp"

void gui::Seg::send(std::string command, ntw::Client &client)
{
    (void)command;
    (void)client;
}

void gui::Seg::receive(std::string command, GameData &gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::string teamName;

    iss >> token >> teamName;

    for (std::size_t i = 0; i < gameData.teamNames().size(); i++) {
        if (gameData.teamNames()[i] == teamName) {
            // gameData.teamNames()[i].setIsDead(true);
            gameData.teamNames().erase(gameData.teamNames().begin() + i);
            break;
        }
    }
}
