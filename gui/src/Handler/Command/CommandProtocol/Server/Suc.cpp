/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Suc
*/

#include "Suc.hpp"

void gui::Suc::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    (void)client;
    (void)parameters;
    std::cerr << "Command suc: can't be staged." << std::endl;
}

void gui::Suc::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    gameData->displayUnknownCommand(command);
}
