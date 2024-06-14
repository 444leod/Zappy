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
    std::cerr << "Command pex: can't be staged." << std::endl;
}

void gui::Pex::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;

    iss >> token >> playerId;
    if (!gameData.playerExists(playerId))
        throw std::invalid_argument("Player does not exist");
    // gameData.players().at(playerId).setIsExpulsed(true);
}
