/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Smg
*/

#include "Smg.hpp"

void gui::Smg::stage(ntw::Client &client, std::string parameters)
{
    (void)client;
    (void)parameters;
    std::cerr << "Command smg: can't be staged." << std::endl;
}

void gui::Smg::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::string message;

    iss >> token >> message;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    // gameData.displayServerMessage(message);
}
