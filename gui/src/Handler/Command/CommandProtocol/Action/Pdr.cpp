/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pdr
*/

#include "Pdr.hpp"

void gui::Pdr::stage(ntw::Client &client, std::string parameters)
{
    (void)parameters;
    (void)client;
}

void gui::Pdr::receive(std::string command, GameData &gameData)
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
        std::cout << "Player " << playerId << " dropped a ressource" << std::endl;
        // gameData.players().at(playerId).dropRessource();
}
