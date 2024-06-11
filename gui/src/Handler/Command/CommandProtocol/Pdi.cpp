/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pdi
*/

#include "Pdi.hpp"

void gui::Pdi::stage(ntw::Client &client, std::string command)
{
    (void)command;
    (void)client;
}

void gui::Pdi::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;

    iss >> token >> playerId;
    // gameData.players().at(playerId).setIsDead(true);
}
