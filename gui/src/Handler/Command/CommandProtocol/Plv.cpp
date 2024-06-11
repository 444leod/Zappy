/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Plv
*/

#include "Plv.hpp"

void gui::Plv::stage(ntw::Client &client, std::string parameters)
{
    std::istringstream iss(parameters);
    std::uint32_t playerLevel;

    iss >> playerLevel;

    client.queueRequest("plv " + std::to_string(playerLevel));
}

void gui::Plv::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;
    std::uint32_t level;

    iss >> token >> playerId >> level;
    // gameData.players().at(playerId)->increasePlayerLevel();
}
