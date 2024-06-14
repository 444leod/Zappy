/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sst
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Sst : public ICommand {
        public:
            /**
             * @brief The command Sst sends the time unit to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief The command Sst receives when the server send the time unit
             * @note Receives the command: sst T
             * @note T -> time unit
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;
    };
}
