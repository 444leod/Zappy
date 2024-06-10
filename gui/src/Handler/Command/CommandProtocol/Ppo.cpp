/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Ppo
*/

#include "Handler/Command/CommandProtocol/Ppo.hpp"

void gui::Ppo::send()
{
    // std::string str = "ppo\n";
    // this->_data->getNetwork()->send(str);
}

gui::Orientation gui::Ppo::getOrientationFromStr(std::string orientation)
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

void gui::Ppo::receive(std::string command, GameData &gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;
    std::uint32_t x, y;
    std::string orientation;

    iss >> token >> playerId >> x >> y >> orientation;
    gameData.players().at(playerId)->setPosition(Vector2u(x, y));
    gameData.players().at(playerId)->setOrientation(getOrientationFromStr(orientation));
}
