/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tna
*/

#include "Handler/Command/CommandProtocol/Tna.hpp"

void gui::Tna::send()
{
    // std::string str = "tna\n";
    // this->_data->getGraphical()->getSocket()->write(str);
}

void gui::Tna::receive(std::string command, GameData &gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::string teamName;
    std::uint32_t teamCount;

    iss >> token >> teamName >> teamCount;
    for (std::uint32_t i = 0; i < teamCount; i++)
        gameData.teamNames().push_back(teamName);
}
