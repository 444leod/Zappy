/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Edi
*/

#include "Edi.hpp"

void gui::Edi::stage(ntw::Client &client, std::string parameters)
{
    (void)parameters;
    (void)client;
}

void gui::Edi::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t eggId;

    iss >> token >> eggId;
    if (!gameData.eggExists(eggId))
        throw std::invalid_argument("Egg does not exist");
    // gameData.eggs().at(eggId).setIsDead(true);
}
