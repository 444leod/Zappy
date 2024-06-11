/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pnw
*/

#include "Pnw.hpp"

void gui::Pnw::stage(ntw::Client &client, std::string parameters)
{
    (void)parameters;
    (void)client;
}

void gui::Pnw::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId, level;
    std::uint32_t x, y;
    std::string orientation;
    std::string teamName;
    Orientation playerOrientation;

    iss >> token >> playerId >> x >> y >> orientation >> level >> teamName;

    auto it = _orientationMap.find(orientation);
    if (it != _orientationMap.end())
        playerOrientation = it->second;
    else
        throw std::invalid_argument("Invalid orientation: " + orientation);
    if (gameData.playerExists(playerId))
        throw std::invalid_argument("Player alreasy exist in the game data with this id.");
    if (level != 1)
        throw std::invalid_argument("Player must spawn as level 1.");
    if (x >= gameData.mapRef().mapSize().x() || y >= gameData.mapRef().mapSize().y())
        throw std::invalid_argument("Player position is out of bounds.");
    if (!gameData.teamExists(teamName))
        throw std::invalid_argument("Team does not exist in the game data.");
    (void)playerOrientation;
    // gui::Character newPlayer;
    // newPlayer.setNewConnection(playerId, Vector2u(x, y), playerOrientation, level, teamName);
    // gameData.addPlayer(std::make_shared<gui::Character>(newPlayer));
}
