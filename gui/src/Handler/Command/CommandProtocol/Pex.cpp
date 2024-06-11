/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pex
*/

#include "Pex.hpp"

void gui::Pex::stage(ntw::Client &client, std::string parameters)
{
    (void)parameters;
    (void)client;
}

void gui::Pex::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;

    iss >> token >> playerId;
    // gameData.players().at(playerId).setIsExpulsed(true);
}
