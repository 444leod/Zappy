/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Mct
*/

#include "Mct.hpp"

void gui::Mct::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    (void)parameters;
    client->queueRequest("mct");
}

void gui::Mct::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    (void)gameData;
    (void)command;
    std::cerr << "Command mct: can't be received." << std::endl;
}
