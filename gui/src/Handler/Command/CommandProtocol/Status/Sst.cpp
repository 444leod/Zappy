/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sst
*/

#include "Sst.hpp"

void gui::Sst::stage(ntw::Client &client, std::string parameters)
{
    std::istringstream iss(parameters);
    std::uint32_t timeUnit;

    iss >> timeUnit;

    client.queueRequest("sst " + timeUnit);
}

void gui::Sst::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t timeUnit;

    iss >> token >> timeUnit;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    // gameData.setUnitTime(timeUnit);
}
