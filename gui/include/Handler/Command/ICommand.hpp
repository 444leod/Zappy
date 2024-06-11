/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ICommand
*/

#pragma once

#include <sstream>
#include <iostream>
#include "Client.hpp"
#include "GameData.hpp"

namespace gui {
    class ICommand {
        public:
            virtual void stage(ntw::Client &client, std::string parameters = "") = 0;
            virtual void receive(std::string command, GameData &gameData) = 0;
    };
}
