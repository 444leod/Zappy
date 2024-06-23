/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pgt
*/

#include "Pgt.hpp"

void gui::Pgt::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    (void)parameters;
    (void)client;
    std::cerr << "Command pgt: can't be staged." << std::endl;
}

void gui::Pgt::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;
    std::uint32_t ressourceNbr;

    iss >> token >> playerId >> ressourceNbr;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    if (!gameData->playerExists(playerId))
        throw std::invalid_argument("Player does not exist");
    auto player = gameData->getPlayerById(playerId);
    for (std::uint32_t i = 0; i < ressourceNbr; i++)
        if (player.has_value())
            player.value()->pickRessource();
}
