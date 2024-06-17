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
            /**
             * @brief The stage function is used to send a command to the server
             * @param client The client
             * @param parameters The parameters
             */
            virtual void stage(ntw::Client &client, std::string parameters = "") = 0;

            /**
             * @brief The receive function is used to receive a command from the server
             * @param command The command given by the server
             * @param gameData The game data
             */
            virtual void receive(std::string command, GameData &gameData) = 0;
    };
}
