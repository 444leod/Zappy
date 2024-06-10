/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Edi
*/

#include "Handler/Command/CommandProtocol/Edi.hpp"

void gui::Edi::send(std::string command, ntw::Client &client)
{
    (void)command;
    (void)client;
}

void gui::Edi::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t eggId;

    iss >> token >> eggId;
    // gameData.eggs().at(eggId).setIsDead(true);
}
