/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ICommand
*/

#pragma once

#include <iostream>
#include <vector>
#include "GameData.hpp"
#include "Client.hpp"

namespace gui {
    class ICommand {
        public:
            ICommand() = default;
            ~ICommand() = default;

            virtual void stage(ntw::Client &client, std::string command) = 0;
            virtual void receive(std::string command, GameData &gameData) = 0;
    };
}
