/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tna
*/

#include "Tna.hpp"

void gui::Tna::stage(ntw::Client &client, std::string parameters)
{
    (void)parameters;
    client.queueRequest("tna");
}

void gui::Tna::receive(std::string command, GameData &gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::string teamName;

    iss >> token >> teamName;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    for (std::size_t i = 0; i < gameData.teamNames().size(); i++)
        gameData.teamNames().push_back(teamName);
}
