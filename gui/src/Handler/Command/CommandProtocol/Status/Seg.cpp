/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Seg
*/

#include "Seg.hpp"

void gui::Seg::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    (void)parameters;
    (void)client;
    std::cerr << "Command seg: can't be staged." << std::endl;
}

void gui::Seg::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::string teamName;

    iss >> token >> teamName;
    if (teamName == "")
        gameData->teamDraw();
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    for (std::size_t i = 0; i < gameData->teamNames().size(); i++) {
        if (gameData->teamNames()[i] == teamName) {
            gameData->teamWin(teamName);
            break;
        } else
            throw std::invalid_argument("Team not found");
    }
}
