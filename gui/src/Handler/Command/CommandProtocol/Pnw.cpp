/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pnw
*/

#include "Pnw.hpp"

void gui::Pnw::stage(ntw::Client &client, std::string command)
{
    (void)command;
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
    // gui::Character newPlayer;
    // newPlayer.setNewConnection(playerId, Vector2u(x, y), playerOrientation, level, teamName);
    // gameData.addPlayer(std::make_shared<gui::Character>(newPlayer));
}
