/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sgt
*/

#include "Sgt.hpp"

void gui::Sgt::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    (void)parameters;
    client->queueRequest("sgt");
}

void gui::Sgt::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t timeUnit;

    iss >> token >> timeUnit;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    gameData->setTimeUnit(timeUnit);
}
