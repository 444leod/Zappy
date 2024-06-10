/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pnw
*/

#include "Handler/Command/CommandProtocol/Pnw.hpp"

void gui::Pnw::send()
{
    return;
}

gui::Orientation gui::Pnw::getOrientationFromStr(std::string orientation)
{
    if (orientation == "NORTH")
        return gui::Orientation::NORTH;
    if (orientation == "EAST")
        return gui::Orientation::EAST;
    if (orientation == "SOUTH")
        return gui::Orientation::SOUTH;
    if (orientation == "WEST")
        return gui::Orientation::WEST;
    return gui::Orientation::NORTH;
}

void gui::Pnw::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;
    std::uint32_t x, y;
    std::string orientation;
    std::uint32_t level;
    std::string teamName;

    iss >> token >> playerId >> x >> y >> orientation >> level >> teamName;
    // gui::Character newPlayer;
    // newPlayer.setNewConnection(playerId, Vector2u(x, y), getOrientationFromStr(orientation), level, teamName);
    // gameData.addPlayer(std::make_shared<gui::Character>(newPlayer));
}
