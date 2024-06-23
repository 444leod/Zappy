/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sbp
*/

#include "Sbp.hpp"

void gui::Sbp::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    (void)client;
    (void)parameters;
    std::cerr << "Command sbp: can't be staged." << std::endl;
}

void gui::Sbp::receive(UNUSED std::string command, UNUSED std::shared_ptr<GameData> gameData)
{
}
