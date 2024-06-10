/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Plv
*/

#include "Handler/Command/CommandProtocol/Plv.hpp"

void gui::Plv::send()
{
    // std::string str = "plv\n";
    // this->_data->getNetwork()->send(str);
}

void gui::Plv::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;
    std::uint32_t level;

    iss >> token >> playerId >> level;
    // gameData.players().at(playerId)->increasePlayerLevel();
}
