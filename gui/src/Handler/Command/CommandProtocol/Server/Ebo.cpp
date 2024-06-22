/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Ebo
*/

#include "Ebo.hpp"

void gui::Ebo::stage(ntw::Client &client, std::string parameters)
{
    (void)client;
    (void)parameters;
    std::cerr << "Command ebo: can't be staged." << std::endl;
}

void gui::Ebo::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t eggId;

    iss >> token >> eggId;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    if (!gameData.eggExists(eggId))
        throw std::invalid_argument("Egg does not exist");
    auto egg = gameData.getEggById(eggId);
    if (egg.has_value())
        egg.value()->hatch();
}
