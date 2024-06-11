/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pgt
*/

#include "Pgt.hpp"

void gui::Pgt::stage(ntw::Client &client, std::string parameters)
{
    (void)parameters;
    (void)client;
}

void gui::Pgt::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;
    std::uint32_t ressourceNbr;

    iss >> token >> playerId >> ressourceNbr;
    if (!gameData.playerExists(playerId))
        throw std::invalid_argument("Player does not exist");
    for (std::uint32_t i = 0; i < ressourceNbr; i++)
        std::cout << "Player " << playerId << " picked up a ressource" << std::endl;
        // gameData.players().at(playerId).pickRessource();
}
