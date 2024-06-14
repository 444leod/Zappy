/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sbp
*/

#include "Sbp.hpp"

void gui::Sbp::stage(ntw::Client &client, std::string parameters)
{
    (void)client;
    (void)parameters;
    std::cerr << "Command sbp: can't be staged." << std::endl;
}

void gui::Sbp::receive(std::string command, GameData &gameData)
{
    (void)command;
    (void)gameData;
    // gameData.displayCommandParameter();
}
