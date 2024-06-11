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
    std::uint32_t playerId;

    iss >> playerId;

    client.queueRequest("plv " + std::to_string(playerId));
}

void gui::Plv::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;
    std::uint32_t level;

    iss >> token >> playerId >> level;

    if (!gameData.playerExists(playerId))
        throw std::runtime_error("Player does not exist in the game data.");
    if (gameData.players().at(playerId)->playerLevel() < level || level > 8 || gameData.players().at(playerId)->playerLevel() > level)
        throw std::runtime_error("Player level received does not match the player level in the game data.");
    // gameData.players().at(playerId)->increasePlayerLevel();
}
