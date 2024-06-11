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
    std::uint32_t teamCount;

    iss >> token >> teamName >> teamCount;
    for (std::uint32_t i = 0; i < teamCount; i++)
        gameData.teamNames().push_back(teamName);
}
