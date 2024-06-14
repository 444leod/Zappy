/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sst
*/

#include "Sst.hpp"

void gui::Sst::stage(ntw::Client &client, std::string parameters)
{
    if (parameters.empty())
        throw std::invalid_argument("Invalid sst arguments");

    client.queueRequest("sst " + parameters);
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
