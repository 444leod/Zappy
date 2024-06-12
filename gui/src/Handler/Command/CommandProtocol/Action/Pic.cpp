/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pic
*/

#include "Pic.hpp"

void gui::Pic::stage(ntw::Client &client, std::string parameters)
{
    (void)parameters;
    (void)client;
}

void gui::Pic::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t x, y;
    std::uint32_t level;
    std::uint32_t playerId;

    iss >> token >> x >> y >> level;

    if (x >= gameData.mapRef().mapSize().x() || y >= gameData.mapRef().mapSize().y())
        throw std::invalid_argument("Invalid tile coordinates, out of map bounds.");
    while (iss >> playerId) {
        if (!gameData.playerExists(playerId))
            throw std::invalid_argument("Player does not exist");
        if (gameData.players().at(playerId)->position().x() != x || gameData.players().at(playerId)->position().y() != y)
            throw std::invalid_argument("Player position does not match the position in the game data.");
        if (gameData.players().at(playerId)->playerLevel() != level)
            throw std::invalid_argument("Player level does not match the level in the game data.");
        // gameData.players().at(playerId).setIsIncantating(true);
    }
}
