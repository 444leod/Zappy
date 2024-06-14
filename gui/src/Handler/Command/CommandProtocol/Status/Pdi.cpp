/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pdi
*/

#include "Pdi.hpp"

void gui::Pdi::stage(ntw::Client &client, std::string parameters)
{
    (void)parameters;
    (void)client;
    std::cerr << "Command pdi: can't be staged" << std::endl;
}

void gui::Pdi::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;

    iss >> token >> playerId;

    if (!gameData.playerExists(playerId))
        throw std::invalid_argument("Player does not exist");
    // gameData.players().at(playerId).setIsDead(true);
}
