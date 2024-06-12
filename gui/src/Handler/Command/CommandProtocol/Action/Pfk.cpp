/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pfk
*/

#include "Pfk.hpp"

void gui::Pfk::stage(ntw::Client &client, std::string parameters)
{
    (void)parameters;
    (void)client;
}

void gui::Pfk::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;

    iss >> token >> playerId;
    if (!gameData.playerExists(playerId))
        throw std::invalid_argument("Player does not exist");
    // gameData.players().at(playerId).isLayingAnEgg(true);
}
