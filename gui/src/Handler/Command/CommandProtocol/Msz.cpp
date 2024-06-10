/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Msz
*/

#include "Handler/Command/CommandProtocol/Msz.hpp"

void gui::Msz::send()
{
    // std::string str = "msz\n";
    // this->_data->getNetwork()->send(str);
}

void gui::Msz::receive(std::string command, GameData &gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t width, height;

    iss >> token >> width >> height;
    Vector2u mapSize(width, height);

    gameData.mapRef().setMapSize(mapSize);
}
