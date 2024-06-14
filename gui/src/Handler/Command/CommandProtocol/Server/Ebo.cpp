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
    std::cerr << "Command ebo: can't be staged" << std::endl;
}

void gui::Ebo::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t eggId;

    iss >> token >> eggId;
    if (!gameData.eggExists(eggId))
        throw std::invalid_argument("Egg does not exist");
    // gameData.eggs().at(eggId).setIsHatched(true);
}
